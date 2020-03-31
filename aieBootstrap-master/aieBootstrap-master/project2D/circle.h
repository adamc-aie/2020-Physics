#pragma once
#include "rigid_body.h"

class circle : public rigid_body
{
public:
	circle(glm::vec2 position, glm::vec2 velocity = glm::vec2(0.0f), float mass = 1.0f, float radius = 1.0f, glm::vec4 colour = glm::vec4(0.1f, 0.1f, 0.8f, 1.0f));
	~circle();

	virtual void make_gizmo();
	virtual bool check_collision(physics_object* pOther);

	const float get_radius() const;
	void set_radius(const float a_radius);

	virtual void debug() override
	{

	}

protected:  
	float radius;



};


