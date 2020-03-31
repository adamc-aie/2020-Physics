#pragma once

#include "Application.h"
#include "Renderer2D.h"

// Forward declaration
class physics_scene;
class circle;
class aligned_bounding_box;

class Application2D : public aie::Application {
public:

	Application2D();
	virtual ~Application2D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Texture*		m_texture;
	aie::Texture*		m_shipTexture;
	aie::Font*			m_font;

	physics_scene* m_physics_scene;
	//aligned_bounding_box* star;
	circle* star;

	float m_timer;
};