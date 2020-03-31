#include "physics_scene.h"
#include "physics_object.h"
#include "rigid_body.h"

#include <list>


const collision_function physics_scene::collision_functions[] =
{
    collision_manager::circle_vs_circle, collision_manager::circle_vs_aabb, collision_manager::circle_vs_line,
    collision_manager::aabb_vs_circle,   collision_manager::aabb_vs_aabb,   collision_manager::aabb_vs_line,
    collision_manager::line_vs_circle,   collision_manager::line_vs_aabb,   collision_manager::line_vs_line
};


physics_scene::physics_scene() : time_step(0.01f), gravity(glm::vec2(0, 0))
{

}
physics_scene::~physics_scene()
{
    for (int i = 0; i < objects.size(); ++i)
    {
        delete objects[i];
        objects[i] = nullptr;
    }
    objects.clear();
}

void physics_scene::add_object(physics_object* a_actor)
{
    objects.push_back(a_actor);
}

void physics_scene::remove_object(physics_object* a_actor)
{
    auto location = std::find(objects.begin(), objects.end(), a_actor);
    objects.erase(location);
    delete a_actor;
    a_actor = nullptr;
}

void physics_scene::update(float a_delta_time)
{

    accumulated_time += a_delta_time;

    while (accumulated_time >= time_step) 
    { 
        for (auto p_object : objects)
        {
            p_object->fixed_update(gravity, time_step);
        }      
        accumulated_time -= time_step;
    }

    static std::list<physics_object*> dirty;

    int object_count = objects.size();

    //need to check for collisions against all objects except this one.
    for (int outer = 0; outer < object_count - 1; outer++)
    {   
        for (int inner = outer + 1; inner < object_count; inner++)
        {    
            physics_object* object1 = objects[outer];
            physics_object* object2 = objects[inner];
            shape shapeId1 = object1->get_shape();
            shape shapeId2 = object2->get_shape();

    // using function pointers
            int functionIdx = (int(shapeId1) * int(shape::shape_count)) + int(shapeId2);
            collision_function collisionFunctionPtr = collision_functions[functionIdx];
            if (collisionFunctionPtr != nullptr)   
            {     
                // did a collision occur?
                auto result = collisionFunctionPtr(object1, object2);
                if (glm::length(result) > 0.001)
                {
                    // Dirty forces stop, remove asap
                    rigid_body* r1 = dynamic_cast<rigid_body*>(object1);
                    rigid_body* r2 = dynamic_cast<rigid_body*>(object2);

                    // Resolve collsion
                    // Separate
                    if (r1 && r2) // even split
                    {
                        r1->set_position(r1->get_position() + 0.5f * result);
                        r2->set_position(r2->get_position() - 0.5f * result);
                        r1->resolve_collision(r2, result);
                    }
                    else if (r1)
                    {
                        r1->set_position(r1->get_position() + result);

                        line* l = dynamic_cast<line*>(object2);
                        l->resolve_collision(r1);

                    }
                    else if (r2)
                    {
                        r2->set_position(r2->get_position() + result);
                        line* l = dynamic_cast<line*>(object1);
                        l->resolve_collision(r2);
                    }

                    // apply reaction force
                }
            }   
        }  
    } 

    // check for collisions (ideally you'd want to have some sort of
    // scene management in place)
    //for (auto p_object : objects) // for (int i = 0; i < count ; ++i)
    //{
    //    for (auto p_other_object : objects) // for (int j = i + 1; j < count ; ++j)
    //    {
    //        if (p_object == p_other_object)
    //            continue;
    //
    //        if (std::find(dirty.begin(), dirty.end(), p_object) != dirty.end() &&
    //            std::find(dirty.begin(), dirty.end(), p_other_object) != dirty.end())
    //            continue;
    //
    //        rigid_body* p_rigid_body = dynamic_cast<rigid_body*>(p_other_object);
    //
    //        if (p_rigid_body->check_collision(p_object))
    //        {
    //            p_rigid_body->apply_force_to_object(dynamic_cast<rigid_body*>(p_object),
    //                p_rigid_body->get_velocity() * p_rigid_body->get_mass());
    //
    //            dirty.push_back(p_rigid_body);
    //            dirty.push_back(p_other_object);
    //        }
    //    }
    //}
    //dirty.clear();
}

void physics_scene::update_gizmos()
{
    for (auto p_object : objects)
    {
        p_object->make_gizmo();
    }
}

