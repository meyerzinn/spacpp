#include <cstdio>
#include <entt/entt.hpp>
#include <string_view>
#include <iostream>
#include <uwebsockets/App.h>
#include <quadtree/Quadtree.h>
#include <chrono>
#include "components.h"
#include "util.h"

constexpr float damping = 0.9;
constexpr std::chrono::nanoseconds timestep(std::chrono::milliseconds(16));

quadtree::Box<float> getBox(quadtreeComponent *node) {
    return node->box;
}

using Quadtree = quadtree::Quadtree<quadtreeComponent *, decltype(&getBox)>;

void processInputs(entt::registry &registry) {

}

void updatePhysics(entt::registry &registry) {
    registry.group<physicsComponent, massComponent>().each([](physicsComponent &physics, massComponent mass) {
        physics.position += physics.velocity * (float) std::chrono::duration<float>(timestep).count();
        physics.velocity *= damping;
    });
}

void updateQuadtree(entt::registry &registry, Quadtree &quad) {
    registry.group<physicsComponent, massComponent, quadtreeComponent>().each(
            [&quad](physicsComponent &physics, massComponent &m, quadtreeComponent &node) {
                vec2 center = cast_vec(node.box.getCenter());
                if (center.dist(physics.position) > 1e-4) {
                    quad.remove(&node);
                    auto radius = massToRadius(m.mass);
                    auto diameter = radius * 2;
                    node.box = quadtree::Box(physics.position.x - radius, physics.position.y - radius, diameter,
                                             diameter);
                    quad.add(&node);
                }
            });
}

void handleCollisions(entt::registry &registry, Quadtree &quad) {
    // broadphase
    auto broadphase = quad.findAllIntersections();
    // nearphase
    std::set<std::pair<entt::entity, entt::entity>> nearphase; // first = larger
    for (auto pair: broadphase) {
        if (registry.has<subcellComponent>(pair.first->id) && registry.has<subcellComponent>(pair.second->id)) {
            auto first_sub = registry.get<subcellComponent>(pair.first->id);
            auto second_sub = registry.get<subcellComponent>(pair.second->id);
            if (first_sub.owner == second_sub.owner) {
                continue; // don't handle collisions between cells owned by the same entity
            }
        }
        auto[first_physics, first_mass] = registry.get<physicsComponent, massComponent>(pair.first->id);
        auto[second_physics, second_mass] = registry.get<physicsComponent, massComponent>(pair.second->id);
        if (std::abs(first_mass.mass - second_mass.mass) / (first_mass.mass + second_mass.mass) < 0.1) {
            continue;// one cell must be 10% larger to consume the other
        }
        if (first_physics.position.dist(second_physics.position) <
            massToRadius(std::max(first_mass.mass, second_mass.mass)) * 0.8) {
            //time for eating
            if (first_mass.mass > second_mass.mass) {
                nearphase.insert(std::pair(pair.first->id, pair.second->id));
            } else {
                nearphase.insert(std::pair(pair.second->id, pair.first->id));
            }
        }
    }
    // resolution
    for (auto pair : nearphase) {
        auto larger_id = pair.first;
        auto smaller_id = pair.second;
    }
    //TODO
}

void processDeadPlayers(entt::registry &registry) {
    registry.view<playerComponent>().each([&registry](entt::entity id, playerComponent &mcc) {
        if (mcc.num_cells <= 0) {
            // kill this player
            registry.destroy(id);
        }
    });
}

int main() {
    int port = 9002;

    // initialize ECS
    entt::registry registry;

    // initialize quadtree
    auto box = quadtree::Box<float>(-1000, -1000, 2000, 2000);
    auto quad = quadtree::Quadtree<quadtreeComponent *, decltype(&getBox)>(box, getBox);

    using WebSocket = uWS::WebSocket<false, true>;

    struct SocketData {
        WebSocket *ws;
    };

    std::thread net([port, &registry, &quad]() {
        uWS::App()
                .get("/hello", [](auto *res, auto *req) {
                    /* You can efficiently stream huge files too */
                    res->writeHeader("Content-Type", "text/html; charset=utf-8")->end("Hello HTTP!");
                })
                .ws<SocketData>("/play", {
                        .compression = uWS::SHARED_COMPRESSOR,
                        .maxPayloadLength = 1024,
                        .idleTimeout = 0,
                        .maxBackpressure = 1 * 1024 * 1024,
                        .open = [](WebSocket *ws, uWS::HttpRequest *req) {
                            std::cout << "connected" << std::endl;
                            SocketData *data = (SocketData *) ws->getUserData();
                            data->ws = ws;
                        },
                        .message = [](auto *ws, std::string_view message, uWS::OpCode opCode) {
                            std::cout << "message: " << message << std::endl;
                            ws->send(message, opCode); // this echoes?
                        },
                        .drain = [](auto *ws) {
                            printf("Drain?");
                            //?
                        },
                        .ping = [](auto *ws) {
                            // respond with pong?
                            printf("Received ping.");
                        },
                        .pong = [](auto *ws) {
                            printf("Received pong.");
                        },
                        .close = [](WebSocket *ws, int code, std::string_view message) {
                            printf("Connection closed.");
                        }
                }).listen("0.0.0.0", 9002, [port, &registry, &quad](auto *token) {
                    if (!token) {
                        std::cout << "No token!" << std::endl;
                    }
                    std::cout << "Listening on port " << port << std::endl;
                }).run();
        std::cout << "Fell through!" << std::endl;
    });


/*
 // Example use of quadtree
        auto entity = registry.create();
        registry.assign<physicsComponent>(entity, vec2f(0, 0), vec2f(100, 100));
        registry.assign<massComponent>(entity, 10);
        quadtree::Box<float> lbox(0, 0, 1, 1);
        auto &nodeVal = registry.assign<quadtreeComponent>(entity, lbox, entity);
        quad.add(&nodeVal);
 */

    // game loop
    using clock = std::chrono::high_resolution_clock;
    std::chrono::nanoseconds lag(std::chrono::nanoseconds(0));
    auto time_start = clock::now();
    bool done = false;

    while (!done) {
        auto current_time = clock::now();
        auto delta_time = current_time - time_start;
        time_start = current_time;
        lag += delta_time;

        while (lag >= timestep) {
            lag -= timestep;

            processInputs(registry);
            updatePhysics(registry);
            updateQuadtree(registry, quad);
            handleCollisions(registry, quad);
        }
        // send network snapshot
    }
    net.join();
    return 0;
}

