#pragma once
#ifndef _RIGID_BODY_H_
#define _RIGID_BODY_H_

#include "physics_object.h"
#include "glm/glm.hpp"

class rigid_body : public physics_object
{
public:
	glm::vec2 get_position() const { return position; }
	glm::vec2 get_velocity() const { return velocity; }
	float get_mass() const { return mass; }

	~rigid_body() {};

	virtual void fixed_update(glm::vec2 a_gravity, float a_time_step);  
	virtual void debug() {};

	// Probably remove this later
	virtual bool check_collision(physics_object * pOther) = 0;

	void apply_force(glm::vec2 force);  
	void apply_force_to_object(rigid_body* a_object, glm::vec2 force);


	void resolve_collision(rigid_body* a_other, glm::vec2 a_collision_normal);

	void set_velocity(glm::vec2 a_velocity) 
	{
		velocity = a_velocity ;
	}

	void set_position(glm::vec2 a_position)
	{
		position = a_position;
	}

protected:
	rigid_body(shape a_shape, glm::vec2 position, glm::vec2 velocity, float mass);
	
	glm::vec2 position;
	glm::vec2 velocity;
	float mass;
	float drag = 0.3f;
};

#endif // !_RIGID_BODY_H_