//
// Created by meyer on 4/6/2020.
//

#ifndef SPACPP_UTIL_H
#define SPACPP_UTIL_H

#include <quadtree/Vector2.h>
#include "vec2.h"
#include "components.h"
#include <functional>
#include <entt/entt.hpp>
#include <quadtree/Quadtree.h>

namespace spacpp {

    constexpr float PI = 3.14159265;
    constexpr float damping = 0.9;
    constexpr std::chrono::nanoseconds timestep(std::chrono::milliseconds(33));

    quadtree::Box<float> getBox(quadtreeComponent *node) {
        return node->box;
    }

    using Quadtree = quadtree::Quadtree<quadtreeComponent *, decltype(&getBox)>;

    template<typename F>
    vec2<F> cast_vec(quadtree::Vector2<F> v) {
        return vec2<F>(v.x, v.y);
    }

    template<typename F>
    quadtree::Vector2<F> cast_vec(vec2<F> v) {
        return quadtree::Vector2<F>(v.x, v.y);
    }

    float massToRadius(float mass) {
        // Area = PI * r * r ==> r = sqrt(Area / PI) ("Area" being a 2D proxy for mass)
        return std::sqrt(mass / PI);
    }

    void removeCell(entt::registry &registry, entt::entity cell_id) {
        auto subcell = registry.try_get<subcellComponent>(cell_id);
        if (subcell != nullptr) {
            entt::entity owner_id = subcell->owner;
            playerComponent *owner = registry.try_get<playerComponent>(owner_id);
            if (owner != nullptr) {
                auto newEnd = std::remove(owner->cells.begin(), owner->cells.begin() + owner->num_cells, cell_id);
                if (newEnd != owner->cells.begin() + owner->num_cells) {
                    owner->num_cells--;
                }
            }
        }
        registry.destroy(cell_id);
    }
}
#endif //SPACPP_UTIL_H
