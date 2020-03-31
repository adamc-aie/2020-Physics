#include "line.h"
#include "rigid_body.h"

line::line(const glm::vec2& a_normal /* = { 0.0f, 1.0f }*/,
			const float a_distance /*= 0.0f*/) :
	normal(a_normal),
	distance_from_origin(a_distance),
	physics_object(shape::line)
{
	set_normal(normal);
}

const glm::vec2 line::get_normal() const
{
	return normal;
}

void line::set_normal(const glm::vec2& a_normal)
{
	if (glm::length(a_normal) <= 0.0f)
	{

	}
	else
	{
		normal = glm::normalize(a_normal);
	}
}

const float line::get_distance() const
{
	return distance_from_origin;
}

void line::set_distance(const float a_distance)
{
	distance_from_origin = a_distance;
}


void line::make_gizmo()
{
	glm::vec2 centre_point = normal * distance_from_origin;
	glm::vec2 draw_direction(normal.y, -normal.x);
	aie::Gizmos::add2DLine(
		centre_point + (draw_direction * 500.0f),
		centre_point - (draw_direction * 500.0f),
		glm::vec4(1.0f));
}

void line::resolve_collision(rigid_body* a_other)
{
	glm::vec2 relativeVelocity = a_other->get_velocity();

	float j =
		glm::dot(-(1 + (elasticity * a_other->elasticity)) * (relativeVelocity), normal)
		/
		glm::dot(normal, normal * (1 / a_other->get_mass()));

	glm::vec2 force = normal * j;

	a_other->apply_force( force );
}