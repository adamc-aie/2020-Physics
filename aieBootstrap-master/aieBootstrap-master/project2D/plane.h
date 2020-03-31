#pragma once
#ifndef _PLANE_H_
#define _PLANE_H_

#include "physics_object.h"

class plane : public physics_object
{
	glm::vec2 normal; // The plane's 'up' face
	float distance; // From origin
};

#endif // !_PLANE_H_
