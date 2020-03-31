#pragma once
#ifndef  _PHYSICS_SCENE_H_
#define _PHYSICS_SCENE_H_

// Supporting includes
#include "glm/glm.hpp"
#include "collision_manager.h"

#include <functional>
using collision_function = std::function< glm::vec2(const physics_object*, const physics_object*) >;

#include <vector>

// Forward declarations
class physics_object;

class physics_scene
{
public:  
    physics_scene();
    ~physics_scene();

    void add_object(physics_object* a_actor);
    void remove_object(physics_object* a_actor);
    void update(float a_delta_time);
    void update_gizmos();

    void set_gravity(const glm::vec2 a_gravity) { gravity = a_gravity; }

    glm::vec2 get_gravity() const { return gravity; }

    void set_time_step(const float a_time_step) { time_step = a_time_step; }
    float get_time_step() const { return time_step; }

protected: 
    float time_step;  
    glm::vec2 gravity;  
    std::vector<physics_object*> objects;


   float accumulated_time = 0.0f;

   static const collision_function collision_functions[];
};

#endif // ! _PHYSICS_SCENE_H_

