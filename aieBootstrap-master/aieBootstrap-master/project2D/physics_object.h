#include "glm/glm.hpp"
#include "Gizmos.h"

#pragma once
#ifndef  _PHYSICS_OBJECT_H_
#define  _PHYSICS_OBJECT_H_

enum class shape : char
{
	//none = 0,
	circle = 0,
	aabb,
	line,
	shape_count
};

class physics_object
{
protected:  
	shape shape_type;
	physics_object(shape a_shape) 
	{
		shape_type = a_shape;
	}

public:  
	virtual void fixed_update(glm::vec2 gravity, float timeStep) = 0;
	virtual void debug() = 0;
	virtual void make_gizmo() = 0;
	virtual void resetPosition() {};

	void set_color(glm::vec4 a_color)
	{
		color = a_color;
	}

	glm::vec4 color = glm::vec4(1.0f);

	shape get_shape() const
	{
		return shape_type;
	}

	float elasticity = 0.5f;
};

#endif // !
