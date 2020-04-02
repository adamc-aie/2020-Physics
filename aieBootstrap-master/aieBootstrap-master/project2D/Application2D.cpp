#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Gizmos.h"

#include "glm/glm.hpp"
#include "glm/ext.hpp"

#include "physics_scene.h"
#include "circle.h"
#include "aligned_bounding_box.h"
#include "line.h"

Application2D::Application2D() 
{

}

Application2D::~Application2D() {

}

bool Application2D::startup()
{
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_2dRenderer = new aie::Renderer2D();

	m_texture = new aie::Texture("./textures/numbered_grid.tga");
	m_shipTexture = new aie::Texture("./textures/ship.png");

	m_font = new aie::Font("./font/consolas.ttf", 32);

	m_physics_scene = new physics_scene();
	m_physics_scene->set_time_step(0.01f);
	m_physics_scene->set_gravity(glm::vec2(0.0f));

	m_timer = 0;

	star = new circle(glm::vec2(-10, 0.0f), glm::vec2(0.0f),
		1.0f, 1.0f, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));


	//star = new aligned_bounding_box(glm::vec2(-10, 0.0f));

	circle* star2 = new circle(glm::vec2(-9, 0.0f), glm::vec2(0.0f),
		1.0f, 0.1f, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	circle* star3 = new circle(glm::vec2(-8, 0.0f), glm::vec2(0.0f),
		1.0f, 0.1f, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

	//circle* earth = new circle(glm::vec2(0.0f, 9.5f), glm::vec2(0.0f),
	//	1.0f, 0.5f, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

	circle* earth = new circle(glm::vec2(0.0f, 9.5f), glm::vec2(0.0f),
		1.0f, 1.0f, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
	//new aligned_bounding_box(glm::vec2(0.0f, 9.5f));

//m_physics_scene->add_object(star2);
//m_physics_scene->add_object(star3);

	line* base = new line(glm::vec2(0.0f, 1.0f), -15.0f);
	line* lid = new line(glm::vec2(0.0f, -1.0f), -15.0f);
	line* lhs = new line(glm::vec2(1.0f, 0.0f), -30.0f);
	line* rhs = new line(glm::vec2(-1.0f, 0.0f), -30.0f);
	line* lhd = new line(glm::vec2(1.0f), -25.0f);
	line* rhd = new line(glm::vec2(-1.0f, 1.0f), -25.0f);
	line* lhdu = new line(glm::vec2(-1.0f), -25.0f);
	line* rhdu = new line(glm::vec2(1.0f, -1.0f), -25.0f);

	m_physics_scene->add_object(base);
	m_physics_scene->add_object(lid);
	m_physics_scene->add_object(lhs);
	m_physics_scene->add_object(rhs);
	m_physics_scene->add_object(lhd);
	m_physics_scene->add_object(rhd);
	m_physics_scene->add_object(lhdu);
	m_physics_scene->add_object(rhdu);

	//aligned_bounding_box* aabb = new aligned_bounding_box(glm::vec2(0.1f, -2.0f));
	for (int x = 0; x <10; ++x)
	{
		for (int y = 0; y < 10; ++y)
		{
			//m_physics_scene->add_object(new aligned_bounding_box(glm::vec2(-8 + x, 3 - y)));
			m_physics_scene->add_object(new circle(glm::vec2(-8 + x, 3 - y)));
		} 
	}

	//m_physics_scene->add_object(new circle(glm::vec2(-100.0f, -2.0f)));
	//m_physics_scene->add_object(new circle(glm::vec2(-10.0f, -2.0f)));
	//m_physics_scene->add_object(new circle(glm::vec2(12.0f, -2.0f)));
	//m_physics_scene->add_object(new circle(glm::vec2(12.0f, -2.0f)));
	//m_physics_scene->add_object(new circle(glm::vec2(12.0f, -2.0f)));
	//m_physics_scene->add_object(new circle(glm::vec2(12.0f, -2.0f)));
	//m_physics_scene->add_object(new circle(glm::vec2(12.0f, -2.0f)));
	//circle* aabb = //new aligned_bounding_box(glm::vec2(0.1f, -2.0f));
	//	new circle(glm::vec2(0.1f, -2.0f), glm::vec2(0.0f),
	//		1.0f, 1.0f, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));


	//m_physics_scene->add_object(aabb);
	//aabb->set_color({ 1.0f, 0.0f, 0.0f, 1.0f });

	m_physics_scene->add_object(earth);
	earth->set_color({ 0.0f, 1.0f, 0.0f, 1.0f });

	m_physics_scene->add_object(star);
	star->set_color({0.0f, 0.0f, 1.0f, 1.0f });
	//m_physics_scene->add_object(earth);

	return true;
}

void Application2D::shutdown() {
	

	aie::Gizmos::destroy();

	delete m_physics_scene;
	//delete m_physics_scene2;
	//delete m_physics_scene3;

	delete m_font;
	delete m_texture;
	delete m_shipTexture;
	delete m_2dRenderer;

}

void Application2D::update(float deltaTime) {

	//deltaTime *= 0.25f;
	m_timer += deltaTime;

	// input example
	aie::Input* input = aie::Input::getInstance();

	// Update the camera position using the arrow keys
	float camPosX;
	float camPosY;
	m_2dRenderer->getCameraPos(camPosX, camPosY);

	if (input->isKeyDown(aie::INPUT_KEY_UP))
		camPosY += 500.0f * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_DOWN))
		camPosY -= 500.0f * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
		camPosX -= 500.0f * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
		camPosX += 500.0f * deltaTime;

	m_2dRenderer->setCameraPos(camPosX, camPosY);

	if (input->wasKeyPressed(aie::INPUT_KEY_SPACE))
	{
		m_physics_scene->set_gravity(glm::vec2(0.0f, -10.0f));
		star->apply_force(glm::vec2(10.0f));

	}

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	
	aie::Gizmos::clear();

	m_physics_scene->update(deltaTime); 
	m_physics_scene->update_gizmos();




}

void Application2D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// demonstrate animation
	/*m_2dRenderer->setUVRect(int(m_timer) % 8 / 8.0f, 0, 1.f / 8, 1.f / 8);
	m_2dRenderer->drawSprite(m_texture, 200, 200, 100, 100);
	
	// demonstrate spinning sprite
	m_2dRenderer->setUVRect(0,0,1,1);
	m_2dRenderer->drawSprite(m_shipTexture, 600, 400, 0, 0, m_timer, 1);
	
	// draw a thin line
	m_2dRenderer->drawLine(300, 300, 600, 400, 2, 1);
	
	// draw a moving purple circle
	m_2dRenderer->setRenderColour(1, 0, 1, 1);
	m_2dRenderer->drawCircle(sin(m_timer) * 100 + 600, 150, 50);
	
	// draw a rotating red box
	m_2dRenderer->setRenderColour(1, 0, 0, 1);
	m_2dRenderer->drawBox(600, 500, 60, 20, m_timer);
	
	// draw a slightly rotated sprite with no texture, coloured yellow
	m_2dRenderer->setRenderColour(1, 1, 0, 1);
	m_2dRenderer->drawSprite(nullptr, 400, 400, 50, 50, 3.14159f * 0.25f, 1);
	
	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	m_2dRenderer->drawText(m_font, "Press ESC to quit!", 0, 720 - 64);*/

	// Draw all batched Gizmos
	aie::Gizmos::draw2D(glm::ortho<float>(-32,32,-18,18,-1,1));

	// done drawing sprites
	m_2dRenderer->end();
}
