#pragma once
#include "physics_object.h"
#include "glm/glm.hpp"

class rigid_body;

class line : public physics_object
{
public:
	

	line(const glm::vec2& a_normal,
		 const float a_distance = 0.0f);

	const glm::vec2 get_normal() const;
	void set_normal(const glm::vec2& a_normal);

	const float get_distance() const;
	void set_distance(const float a_distance);

	void debug() override {}
	void fixed_update(glm::vec2 gravity, float timeStep) override {};
	void make_gizmo() override;


	void resolve_collision(rigid_body* a_other);

private:
	glm::vec2 normal = glm::vec2(0,1);
	float distance_from_origin = 0.0f;
};

