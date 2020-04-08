//
// Created by meyer on 4/6/2020.
//

#ifndef SPACPP_UTIL_H
#define SPACPP_UTIL_H

#include <quadtree/Vector2.h>
#include "vec2.h"
#include "components.h"

constexpr float PI = 3.14159265;

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

#endif //SPACPP_UTIL_H
