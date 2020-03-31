#include "circle.h"
#include <cmath>

#include "collision_manager.h"

circle::circle(glm::vec2 a_position, glm::vec2 a_velocity, float a_mass, float a_radius, glm::vec4 a_colour) :
	rigid_body(shape::circle, a_position, a_velocity, a_mass) , radius(a_radius)
{
	color = a_colour;
}

circle::~circle() {}

const float circle::get_radius() const
{
	return radius;
}
void circle::set_radius(const float a_radius)
{
	radius = abs(a_radius);
}

void circle::make_gizmo()
{
	aie::Gizmos::add2DCircle(position, radius, 32, color);
}

bool circle::check_collision(physics_object* pOther)
{
	return false;
	//return collision_manager::circle_vs_circle(*this, (circle&)*pOther);
}

