//
// Created by meyer on 4/12/2020.
//

#ifndef SPACPP_PHYSICS_H
#define SPACPP_PHYSICS_H

#include <cmath>
#include <entt/entity/registry.hpp>
#include <quadtree/Quadtree.h>
#include "components.h"
#include "util.h"

namespace spacpp {
    void updatePhysics(entt::registry &registry) {
        registry.view<physicsComponent>().each([](physicsComponent &physics) {
            physics.position += physics.velocity * std::chrono::duration<float>(timestep).count();
            physics.velocity *= damping;
        });
    }

    void updateQuadtree(entt::registry &registry, Quadtree &quad) {
        registry.group<const physicsComponent, const massComponent, quadtreeComponent>().each(
                [&quad](const physicsComponent &physics, const massComponent &m, quadtreeComponent &node) {
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
        // it's a cell-eat-cell world

        // NOTE: this is probably one of the slower paths of the game loop because it involves essentially random access
        // into the ECS. Hopefully it doesn't matter because there shouldn't be very many cells eaten per tick.
        // TODO: Profile
        for (auto pair : nearphase) {
            auto larger_id = pair.first;
            auto smaller_id = pair.second;

            // since we edit mass in-place, if multiple cells could consume the same cell, we don't risk duplicating the
            // mass of the consumed cell.

            auto larger_mass = registry.try_get<massComponent>(larger_id);
            auto smaller_mass = registry.try_get<massComponent>(smaller_id);
            if (larger_mass == nullptr || smaller_mass == nullptr) {
                continue;
            }
            larger_mass->mass += smaller_mass->mass * .9; // 10% mass penalty to discourage teaming
            removeCell(registry, smaller_id);
        }
    }

    void processDeadPlayers(entt::registry &registry) {
        registry.view<playerComponent>().each([&registry](entt::entity id, playerComponent &mcc) {
            if (mcc.num_cells <= 0) {
                // send death message
            }
        });
    }
}
#endif //SPACPP_PHYSICS_H
