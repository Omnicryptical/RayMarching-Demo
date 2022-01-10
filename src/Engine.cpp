#include "Engine.h"

Keyboard Engine::keyboard = Keyboard();
Mouse Engine::mouse = Mouse();

Engine::Engine()
{
	/* Initialize the library */
	if (!glfwInit())
	{
		appReturn = -1;
		QUIT = true;
		return;
	}

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#define FULLSCREEN false

	/* Create a windowed mode window and its OpenGL context */
	if (FULLSCREEN) {
        window = glfwCreateWindow(700, 700, "OpenGL", glfwGetPrimaryMonitor(), NULL);
	}
	else
	{
        window = glfwCreateWindow(700, 700, "OpenGL", NULL, NULL);
	}
	if (!window)
	{
		glfwTerminate();
		appReturn = -1;
		QUIT = true;
		return;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		std::cout << "glewInit() FAILED!" << std::endl;
	}

	renderer = new Renderer();

	//Set Up Input
	glfwSetKeyCallback(window, key_callback);

	glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

Engine::~Engine()
{
	delete renderer;
	glfwTerminate();
}

int Engine::Loop()
{
	ft.Mark();
	ft.SetDuration();
	dtv = ft.deltaTime * frameConstant;
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window) && !QUIT)
	{
		counter++;
		ft.Mark();

		Events();
		Update();
		Render();

		ft.SetDuration();
		if (counter > 100) {
			std::cout << ft.deltaTime << " " << 1 / ft.deltaTime << std::endl;
			counter = 0;
		}
		dtv = ft.deltaTime * frameConstant;
	}

	return appReturn;
}

void Engine::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		keyboard.keys[key] = true;
	}
	if (action == GLFW_RELEASE)
	{
		keyboard.keys[key] = false;
	}
}

void Engine::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	mouse.change = true;
	mouse.px = mouse.x;
	mouse.py = mouse.y;
	mouse.x = float(xpos);
	mouse.y = float(ypos);
	mouse.dx = mouse.x - mouse.px;
	mouse.dy = mouse.y - mouse.py;
}

void Engine::Events()
{
	/* Poll for and process events */
	glfwPollEvents();
}

void Engine::Update()
{
    renderer->updateTime(ft.deltaTime);

	if (keyboard.keys[GLFW_KEY_ESCAPE])
	{
		QUIT = true;
	}
    if (keyboard.keys[GLFW_KEY_R])
    {
        renderer->reloadShaders();
    }

	if (mouse.change == true) {
        //Rotate Around Y Axis
        renderer->rotateCameraPitch(-mouse.dx * dtv * 0.001f);
		//Rotate Camera Vertically
        renderer->rotateCameraYaw(0.001f*dtv*mouse.dy);
	}
	//Translate Camera Position
	renderer->shiftCamera(
	0,
	movementSpeed* dtv*keyboard.keys[GLFW_KEY_SPACE] -
		movementSpeed* dtv*keyboard.keys[GLFW_KEY_LEFT_SHIFT],
	0);
	//Move Camera Foreward
	renderer->moveCamera(
        - movementSpeed * dtv*keyboard.keys[GLFW_KEY_W]
        + movementSpeed * dtv*keyboard.keys[GLFW_KEY_S]);
	//Strafe Camera
	renderer->strafeCamera(
		movementSpeed * dtv*keyboard.keys[GLFW_KEY_D]
		- movementSpeed * dtv*keyboard.keys[GLFW_KEY_A]);

	//Adjust movement speed
		movementSpeed *= 1+0.01f*(dtv*keyboard.keys[GLFW_KEY_UP]
		-dtv*keyboard.keys[GLFW_KEY_DOWN]);

    for (Object& c : objects)
	{
		c.Update(ft.deltaTime);
	}

    if (keyboard.keys[GLFW_KEY_KP_1]) renderer->lightingDirection.x += .1;
    if (keyboard.keys[GLFW_KEY_KP_7]) renderer->lightingDirection.x -= .1;
    if (keyboard.keys[GLFW_KEY_KP_2]) renderer->lightingDirection.y += .1;
    if (keyboard.keys[GLFW_KEY_KP_8]) renderer->lightingDirection.y -= .1;
    if (keyboard.keys[GLFW_KEY_KP_3]) renderer->lightingDirection.z += .1;
    if (keyboard.keys[GLFW_KEY_KP_9]) renderer->lightingDirection.z -= .1;

    if (glm::length(renderer->lightingDirection) > 1.0f) renderer->lightingDirection = glm::normalize(renderer->lightingDirection);

	mouse.change = false;
	mouse.dx = 0;
	mouse.dy = 0;
}

void Engine::Render()
{
	/* Render here */
    glClearColor(0.5f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderer->renderPresent();

	/* Swap front and back buffers */
	glfwSwapBuffers(window);
}
