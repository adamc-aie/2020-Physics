#pragma once
#include "rigid_body.h"

class aligned_bounding_box : public rigid_body
{
public:
	aligned_bounding_box(const glm::vec2& a_position,
						 const glm::vec2& a_extents = glm::vec2(1.0f),
						 const glm::vec2& a_velocity = glm::vec2(0.0f),
						 const float a_mass = 1.0f);

	const glm::vec2 get_position() const;
	void set_position(const glm::vec2& a_position);

	const glm::vec2 get_extents() const;
	void set_extents(const glm::vec2& a_extents);

	const float get_width() const;
	const float get_height() const;

	const glm::vec2 get_min() const;
	const glm::vec2 get_max() const;

	// Implementation of the base class virtual members
	void debug() override {}
	bool check_collision(physics_object* pOther) override { return false; }
	void make_gizmo() override 
	{
		aie::Gizmos::add2DAABBFilled(position, extents * 0.5f, color);
	}

private:
	union
	{
		glm::vec2 extents;
		struct
		{
			float width;
			float height;
		};
	};
};

