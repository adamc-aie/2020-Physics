#include "collision_manager.h"

#include <cmath>


glm::vec2 collision_manager::circle_vs_circle(
	const physics_object* a_circle_A,
	const physics_object* a_circle_B)
{
	const circle* c1 = dynamic_cast<const circle*>(a_circle_A);
	const circle* c2 = dynamic_cast<const circle*>(a_circle_B);

	assert(c1 && c2 && " Circle or Line was null in collision check");

	glm::vec2 displacement = (c1->get_position() - c2->get_position());
	float sum_of_radii = c1->get_radius() + c2->get_radius();
	float overlap = (sum_of_radii) - glm::length(displacement);

	if(overlap > 0.0f)
	{
		return glm::normalize(displacement) * overlap;
	}
	return glm::vec2(0.0f);
}

glm::vec2 collision_manager::aabb_vs_aabb(const physics_object* a_aabb_a, const physics_object* a_aabb_b)
{
	const aligned_bounding_box* aabb_a = dynamic_cast<const aligned_bounding_box*>(a_aabb_a);
	const aligned_bounding_box* aabb_b = dynamic_cast<const aligned_bounding_box*>(a_aabb_b);
	
	const float max_overlap = 10000000.0f;
	float overlap = max_overlap; //<- numeric float limit would be a better choice
	
	glm::vec2 overlap_vector = glm::vec2(0.0f);


	// Given A and B are aabbs, lets check each axis for an overlap.
	if (aabb_a->get_max().x > aabb_b->get_min().x)
	{
		float local_overlap = abs( aabb_a->get_max().x - aabb_b->get_min().x);
		if (local_overlap < overlap)
		{
			overlap = local_overlap;
			overlap_vector = glm::vec2(-overlap, 0);
		}
	}
	else
	{
		return glm::vec2(0.0f);
	}

	// Check the other side
	if (aabb_a->get_min().x < aabb_b->get_max().x)
	{
		float local_overlap = abs(aabb_a->get_min().x - aabb_b->get_max().x);
		if (local_overlap < overlap)
		{
			overlap = local_overlap;
			// Other direction along x
			overlap_vector = glm::vec2(overlap,0);
		}
	}
	else
	{
		return glm::vec2(0.0f);
	}

	// Y axis check
	if (aabb_a->get_max().y > aabb_b->get_min().y)
	{
		float local_overlap = abs(aabb_a->get_max().y - aabb_b->get_min().y);
		if (local_overlap < overlap)
		{
			overlap = local_overlap;
			overlap_vector = glm::vec2(0, -overlap);
		}
	}
	else
	{
		return glm::vec2(0.0f);
	}

	// Check the other side
	if (aabb_a->get_min().y < aabb_b->get_max().y)
	{
		float local_overlap = abs(aabb_a->get_min().y - aabb_b->get_max().y);
		if (local_overlap < overlap)
		{
			overlap = local_overlap;
			// Other direction along y
			overlap_vector = glm::vec2(0, overlap);
		}
	}
	else
	{
		return glm::vec2(0.0f);
	}

	return overlap_vector;
}

glm::vec2 collision_manager::line_vs_line(const physics_object* a_line_A, const physics_object* a_line_B)
{
	return glm::vec2(0.0f);
}

glm::vec2 collision_manager::aabb_vs_circle(const physics_object* a_aabb, const physics_object* a_circle)
{
	const aligned_bounding_box* aabb = dynamic_cast<const aligned_bounding_box*>(a_aabb);
	const circle* c = dynamic_cast<const circle*>(a_circle);

	glm::vec2 clamped_centre = glm::clamp(c->get_position(), aabb->get_min(), aabb->get_max());

	glm::vec2 displacement = clamped_centre - c->get_position();

	float overlap = c->get_radius() - glm::length(displacement);

	if (overlap > 0.0f)
	{
		return glm::normalize(displacement) * overlap;
	}

	return glm::vec2(0.0f);
}

glm::vec2 collision_manager::circle_vs_aabb(const physics_object* a_circle, const physics_object* a_aabb)
{
	return aabb_vs_circle(a_aabb, a_circle);
}

glm::vec2 collision_manager::circle_vs_line(const physics_object* a_circle, const physics_object* a_line)
{
	const circle* c = dynamic_cast<const circle*>(a_circle);
	const line* l = dynamic_cast<const line*>(a_line);

	assert(c && l && " Circle or Line was null in collision check");

	float position_dot_normal = glm::dot(c->get_position(), l->get_normal());

	float distance = position_dot_normal - (l->get_distance() + c->get_radius());

	if (distance < 0.0f)
		return -(l->get_normal()) * distance;
	else
		return glm::vec2(0.0f);
}

glm::vec2 collision_manager::line_vs_circle(const physics_object* a_line, const physics_object* a_circle)
{
	return circle_vs_line(a_circle, a_line);
}

glm::vec2 collision_manager::aabb_vs_line(const physics_object* a_aabb,	const physics_object* a_line)
{
	// #1 loop each corner and dot product the distance
	//		then the furthest negative distance is the corner of greatest overlap
	// float position_dot_normal =
	//	a_aabb.get_max().dot(a_line.get_normal());
	// float distance = position_dot_normal - a_line.get_distance();
	const aligned_bounding_box* aabb = dynamic_cast<const aligned_bounding_box*>(a_aabb);
	const line* l = dynamic_cast<const line*>(a_line);

	glm::vec2 extents = 0.5f * aabb->get_extents();
	glm::vec2 extents_neg_x = 0.5f * glm::vec2(-aabb->get_extents().x, aabb->get_extents().y);

	float dot_extents = glm::dot(extents, l->get_normal());
	float dot_extents_neg_x = glm::dot(extents_neg_x, l->get_normal());

	float radius = fmaxf(fabsf(dot_extents), fabsf(dot_extents_neg_x));

	circle projection( aabb->get_position(), glm::vec2(0.0f), aabb->get_mass(), radius, glm::vec4(0.0f));
	return circle_vs_line(&projection, a_line);
}

glm::vec2 collision_manager::line_vs_aabb(const physics_object* a_line,	const physics_object* a_aabb)
{
	return aabb_vs_line(a_aabb, a_line);
}


/*
bool collision_manager::aabb_vs_aabb(
	const aligned_bounding_box& a_aabb_A,
	const aligned_bounding_box& a_aabb_B)
{
	return !(a_aabb_A.get_max().x < a_aabb_B.get_min().x ||
			 a_aabb_A.get_min().x > a_aabb_B.get_max().x ||
			 a_aabb_A.get_max().y < a_aabb_B.get_min().y ||
			 a_aabb_A.get_min().y > a_aabb_B.get_max().y);
}

bool collision_manager::aabb_vs_circle(
	const aligned_bounding_box& a_aabb,
	const circle& a_circle)
{
	glm::vec2 clamped_centre = clamp(a_circle.get_position(), a_aabb.get_min(), a_aabb.get_max());
	glm::vec2 displacement = clamped_centre - a_circle.get_position();
	return (displacement.magnitude() < a_circle.get_radius());
}

bool collision_manager::circle_vs_line(
	const circle& a_circle,
	const line& a_line)
{
	float position_dot_normal = 
		a_circle.get_position().dot(a_line.get_normal());
	float distance = position_dot_normal -
		(a_line.get_distance() + a_circle.get_radius());
	return (distance < 0);
}

bool collision_manager::aabb_vs_line(
	const aligned_bounding_box& a_aabb,
	const line& a_line)
{
	// #1 loop each corner and dot product the distance
	//		then the furthest negative distance is the corner of greatest overlap
	// float position_dot_normal =
	//	a_aabb.get_max().dot(a_line.get_normal());
	// float distance = position_dot_normal - a_line.get_distance();

	glm::vec2 extents = 0.5f * a_aabb.get_extents();
	glm::vec2 extents_neg_x = 0.5f * glm::vec2(-a_aabb.get_extents().x, a_aabb.get_extents().y);
	
	float dot_extents = extents.dot(a_line.get_normal());
	float dot_extents_neg_x = extents_neg_x.dot(a_line.get_normal());

	float radius = fmaxf(fabsf(dot_extents), fabsf(dot_extents_neg_x));

	circle projection{ a_aabb.get_position() , radius };
	return circle_vs_line(projection, a_line);
}

glm::vec2 collision_manager::clamp(
	const glm::vec2& a_glm::vec2,
	const glm::vec2& a_min,
	const glm::vec2& a_max)
{
	return { fminf(fmaxf(a_glm::vec2.x, a_min.x), a_max.x),
			 fminf(fmaxf(a_glm::vec2.y, a_min.y), a_max.y) };
}

*/