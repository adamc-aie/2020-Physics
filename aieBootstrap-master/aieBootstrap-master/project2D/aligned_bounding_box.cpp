#include "aligned_bounding_box.h"
#include <cmath>

aligned_bounding_box::aligned_bounding_box(
	const glm::vec2& a_position,
	const glm::vec2& a_extents, /* = glm::vec2(1.0f) */
	const glm::vec2& a_velocity, /* = glm::vec2(0.0f) */
	const float a_mass /* = 1.0f*/)
	:
	rigid_body(shape::aabb, a_position, a_velocity, a_mass),
	extents(a_extents)
{}

const glm::vec2 aligned_bounding_box::get_position() const
{
	return position;
}

void aligned_bounding_box::set_position(const glm::vec2& a_position)
{
	position = a_position;
}

const glm::vec2 aligned_bounding_box::get_extents() const
{
	return extents;
}

void aligned_bounding_box::set_extents(const glm::vec2& a_extents)
{
	extents = { abs(a_extents.x), abs(a_extents.y) };
}

const float aligned_bounding_box::get_width() const
{
	return width;
}

const float aligned_bounding_box::get_height() const
{
	return height;
}

const glm::vec2 aligned_bounding_box::get_min() const
{
	return position - 0.5f * extents;
}

const glm::vec2 aligned_bounding_box::get_max() const
{
	return position + 0.5f * extents;
}