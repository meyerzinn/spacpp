#include <entt/entt.hpp>
#include <string_view>
#include <iostream>
#include <uwebsockets/App.h>
#include <chrono>
#include <boost/lockfree/queue.hpp>
#include <flatbuffers/flatbuffers.h>
#include "components.h"
#include "util.h"
#include "physics.h"
#include "net.h"

using namespace spacpp;

int main() {
    int port = 9002;

    // initialize task queue
    using task = std::function<void()>;
    boost::lockfree::queue<task *> task_queue(128);

    // initialize ECS
    entt::registry registry;

    // initialize quadtree
    auto box = quadtree::Box<float>(0, 0, 10000, 10000);
    auto quad = Quadtree(box, getBox);

    std::thread net([port, &task_queue, &registry, &quad]() {
        uWS::SSLApp({
                            .key_file_name="certs/key.pem",
                            .cert_file_name="carts/cert.pem"
                    })
                .get("/hello", [](auto *res, auto *req) {
                    /* You can efficiently stream huge files too */
                    res->writeHeader("Content-Type", "text/html; charset=utf-8")->end("Hello HTTP!");
                })
                .ws<socketData>("/play", {
                        .compression = uWS::SHARED_COMPRESSOR,
                        .maxPayloadLength = 1024,
                        .idleTimeout = 0,
                        .maxBackpressure = 1 * 1024 * 1024,
                        .open = [&task_queue, &registry](WebSocket *ws, uWS::HttpRequest *req) {
                            std::cout << "connected" << std::endl;
                            task tsk = [&registry, &ws]() {
                                auto *data = (socketData *) ws->getUserData();
                                data->id = registry.create();
                                registry.assign<WebSocket *>(data->id, ws);
                            };
                            while (!task_queue.push(&tsk)) {}
                        },
                        .message = [](auto *ws, std::string_view message, uWS::OpCode opCode) {
                            std::cout << "message: " << message << std::endl;
                            ws->send(message, opCode); // this echoes?
                        },
                        .drain = [](auto *ws) {
                            std::cout << "Drain?" << std::endl;
                        },
                        .ping = [](auto *ws) {
                            // respond with pong?
                            std::cout << "Received ping." << std::endl;
                        },
                        .pong = [](auto *ws) {
                            std::cout << "Received pong." << std::endl;
                        },
                        .close = [](WebSocket *ws, int code, std::string_view message) {
                            std::cout << "Connection closed." << std::endl;
                        }
                }).listen("0.0.0.0", port, [port, &registry, &quad](auto *token) {
                    if (!token) {
                        std::cout << "No token!" << std::endl;
                    }
                    std::cout << "Listening on port " << port << std::endl;
                }).run();
        std::cout << "Stopping server." << std::endl;
    });

    std::thread game([&task_queue, &registry, &quad]() {
        // game loop
        using clock = std::chrono::high_resolution_clock;
        std::chrono::nanoseconds lag(std::chrono::nanoseconds(0));
        auto time_start = clock::now();

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
        while (true) {
            auto current_time = clock::now();
            auto delta_time = current_time - time_start;
            time_start = current_time;
            lag += delta_time;

            while (lag >= timestep) {
                lag -= timestep;
                // exhaust synchronous task channel
                task *t = nullptr;
                while (task_queue.pop(t)) {
                    (*t)();
                    delete t;
                }
                // run world update
                updatePhysics(registry);
                updateQuadtree(registry, quad);
                handleCollisions(registry, quad);
            }
            sendWorldUpdates(registry, quad);
        }
#pragma clang diagnostic pop
        std::cout << "Game loop ended." << std::endl;
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

    game.join();
    net.join();
    return 0;
}

