//
// Created by meyer on 4/3/2020.
//

#include <cmath>
#include <entt/entity/registry.hpp>
#include <quadtree/Quadtree.h>
#include "components.h"



//void updateBoundingBox(entt::registry &registry) {
//    registry.view<position, mass, boundingBox>().each([](auto &position, auto &massive, auto &boundingBox) {
//        auto radius = sqrt(massive.mass / M_PI);
//        boundingBox.min[0] = position[0] - radius;
//        boundingBox.min[1] = position[1] - radius;
//        boundingBox.max[0] = position[0] + radius;
//        boundingBox.max[1] = position[1] + radius;
//    });
//}
