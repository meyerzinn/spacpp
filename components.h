//
// Created by meyer on 4/3/2020.
//

#ifndef SPACPP_COMPONENTS_H
#define SPACPP_COMPONENTS_H

#include <quadtree/Box.h>
#include "vec2.h"
#include <entt/entt.hpp>
#include <uwebsockets/WebSocket.h>
#include <array>
#include <boost/lockfree/spsc_queue.hpp>
#include <unordered_set>

namespace spacpp {
    using WebSocket = uWS::WebSocket<true, true>;

    struct massComponent {
        float mass;
    };

    struct physicsComponent {
        vec2f position, velocity;
    };

    struct quadtreeComponent {
        quadtree::Box<float> box;
        entt::entity id{};
    };

// marks a cell as a sub-cell of an entity
    struct subcellComponent {
        entt::entity owner;
    };

    struct playerComponent {
        std::array<entt::entity, 16> cells;
        int num_cells;
        vec2f lastCenter;
        float lastTotalMass;
        std::string name;
    };

    struct controllerComponent {
        vec2f direction;
    };

    struct socketData {
        entt::entity id = entt::null;
        std::unordered_set<entt::entity> knownEntities = {};
        boost::lockfree::spsc_queue<vec2f, boost::lockfree::capacity<128>> inputs;

        void knows(entt::entity other, bool known) {
            if (known) {
                knownEntities.insert(other);
            } else {
                knownEntities.erase(other);
            }
        }

        bool knows(entt::entity other) {
            return knownEntities.find(other) != knownEntities.end();
        };

    };
}
#endif //SPACPP_COMPONENTS_H