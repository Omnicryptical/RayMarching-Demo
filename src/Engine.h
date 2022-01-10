#pragma once

#include "GLInclude.h"
#include "Renderer.h"
#include "Keyboard.h"
#include "Mouse.h"
#include <iostream>
#include "Dice.h"
#include "FrameTimer.h"
#include "Object.h"


class Engine
{
private:
	
	bool QUIT = false;
	int appReturn = 0;

	FrameTimer ft;
    float frameConstant = 600;
	float dtv = 0;
	int counter = 0;

	GLFWwindow* window;
	Renderer* renderer;

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

	//Vars

    std::vector<Object> objects;

    float movementSpeed = 0.006f;

public:
	static Keyboard keyboard;
	static Mouse mouse;

	Engine();
	~Engine();

	int Loop();

	void Events();
	void Update();
	void Render();

private:
};
