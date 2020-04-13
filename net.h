//
// Created by meyer on 4/12/2020.
//

#ifndef SPACPP_NET_H
#define SPACPP_NET_H

#include <entt/entt.hpp>
#include "components.h"
#include "util.h"
#include <vector>
#include <chrono>
#include "packets_generated.h"
#include <flatbuffers/flatbuffers.h>
#include "vec2.h"
#include <boost/range/algorithm/set_algorithm.hpp>

namespace spacpp {
    inline protocol::vec2f encode_vec2f(vec2f v) {
        return protocol::vec2f(v.x, v.y);
    }

    void sendWorldUpdates(entt::registry &registry, const Quadtree &quad) {
        std::int64_t timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        registry.group<WebSocket *, playerComponent>().each(
                [&registry, &quad, timestamp](WebSocket *ws, playerComponent &player) {
                    auto *data = (socketData *) ws->getUserData();
                    if (player.num_cells > 0) {
                        player.lastCenter = vec2f(0, 0);
                        player.lastTotalMass = 0;
                        for (int i = 0; i < player.num_cells; i++) {
                            auto cell_id = player.cells[i];
                            auto[physics, mass] = registry.get<physicsComponent, massComponent>(cell_id);
                            player.lastCenter += physics.position;
                            player.lastTotalMass += mass.mass;
                        }
                        player.lastCenter /= player.num_cells;
                    }
                    // visibility needs to scale as a function of total radius
                    auto radius = massToRadius(player.lastTotalMass);
                    auto diameter = radius * 2;
                    std::vector<quadtreeComponent *> nearby = quad.query(
                            quadtree::Box(player.lastCenter.x - radius, player.lastCenter.y - radius,
                                          diameter, diameter));

                    //TODO  probably should initialize outside the loop and have a shared, larger buffer
                    flatbuffers::FlatBufferBuilder builder(1024);
                    std::vector<entt::entity> entities;
                    std::vector<flatbuffers::Offset<void>> entitySnapshots;
                    std::vector<protocol::CellDelta> cellDeltas;
                    for (auto qcc : nearby) {
                        auto id = qcc->id;
                        entities.push_back(id);
                        if (auto[mass, physics] = registry.try_get<massComponent, physicsComponent>(id);
                                mass != nullptr && physics != nullptr) {
                            if (!data->knows(id)) {
                                data->knows(id, true);
                                if (auto subcell = registry.try_get<subcellComponent>(id); subcell != nullptr) {
                                    // it's a player cell
                                    if (!data->knows(subcell->owner)) {
                                        // make sure client knows the subcell's player as well
                                        data->knows(subcell->owner, true);
                                        auto owner = registry.get<playerComponent>(subcell->owner);
                                        auto nameStr = builder.CreateString(owner.name);
                                        auto playerSnapshot = protocol::CreatePlayerSnapshot(builder,
                                                                                             (std::uint32_t) subcell->owner,
                                                                                             nameStr);
                                        entitySnapshots.push_back(playerSnapshot.Union());
                                    }
                                    auto playerCellSnapshot = protocol::CreatePlayerCellSnapshot(builder,
                                                                                                 (std::uint32_t) id,
                                                                                                 (std::uint32_t) subcell->owner);
                                    entitySnapshots.push_back(playerCellSnapshot.Union());
                                } else {
                                    // it's a food cell
                                    auto posn = encode_vec2f(physics->position);
                                    auto foodCellSnapshot = protocol::CreateFoodCellSnapshot(builder,
                                                                                             (std::uint32_t) id,
                                                                                             &posn,
                                                                                             mass->mass);
                                    entitySnapshots.push_back(foodCellSnapshot.Union());
                                }
                            }
                            // send deltas
                            if (physics->velocity.length() > 1e-4) {
                                auto posn = encode_vec2f(physics->position);
                                auto velocity = encode_vec2f(physics->velocity);
                                float m = mass->mass;
                                auto cellDelta = protocol::CellDelta((std::uint32_t) id, posn, velocity, m);
                                cellDeltas.push_back(cellDelta);
                            }
                        }
                    }
                    auto snapshots = builder.CreateVector(entitySnapshots);
                    auto deltas = builder.CreateVectorOfNativeStructs<protocol::CellDelta>(cellDeltas);
                    std::unordered_set<entt::entity> deletes;
                    boost::set_difference(data->knownEntities, entities, deletes);
                    for (auto d: deletes) {
                        data->knows(d, false);
                    }
                    auto worldUpdate = protocol::CreateWorldUpdate(builder, builder.CreateVector(deletes), snapshots, deltas);

                }

        );
    }
}
#endif //SPACPP_NET_H
