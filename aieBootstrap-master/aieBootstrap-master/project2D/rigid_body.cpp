#include "rigid_body.h"
//rigid_body(shape a_shape, const glm::vec2& a_position)
//	: position(a_position), physics_object(a_shape) {}

rigid_body::rigid_body(
    shape a_shape, 
    glm::vec2 a_position,
    glm::vec2 a_velocity, 
    float a_mass) : 
        physics_object(a_shape),
        position(a_position), 
        velocity(a_velocity),
        mass(a_mass)
{}

void rigid_body::fixed_update(glm::vec2 a_gravity, float a_time_step)
{
    apply_force(a_gravity * mass * a_time_step);
    velocity -= velocity * drag * a_time_step;
    position += velocity * a_time_step;
}


void rigid_body::apply_force(glm::vec2 force)
{
    velocity += force / mass; // a = F / m
}

void rigid_body::apply_force_to_object(rigid_body* a_object, glm::vec2 force)
{
    a_object->apply_force(force);
    this->apply_force(-force);
}

void rigid_body::resolve_collision(rigid_body* a_other, glm::vec2 a_collision_normal)
{
    glm::vec2 normal = glm::normalize(a_collision_normal);

    glm::vec2 relativeVelocity = a_other->get_velocity() - velocity;

    
    float j = 
        glm::dot( -(1 + (elasticity * a_other->elasticity)) * (relativeVelocity), normal)
                                /
        glm::dot(normal, normal * ((1 / mass) + (1 / a_other->get_mass())));

    glm::vec2 force = normal * j;

    apply_force_to_object (a_other, force);
}

