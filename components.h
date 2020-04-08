//
// Created by meyer on 4/3/2020.
//

#ifndef SPACPP_COMPONENTS_H
#define SPACPP_COMPONENTS_H

#include <quadtree/Box.h>
#include "vec2.h"
#include <entt/entt.hpp>
#include <uwebsockets/WebSocket.h>

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
    entt::entity cells[16];
    int num_cells;
};

struct controllerComponent {
    vec2f direction;
};

struct networkComponent {
    uWS::WebSocket<false, true> *ws;
};

#endif //SPACPP_COMPONENTS_H