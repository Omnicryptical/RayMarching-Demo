#include "Renderer.h"
#include "Object.h"

Renderer::Renderer()
{

    GLCall(glGenVertexArrays(1, &vertexArrayObject));
    GLCall(glBindVertexArray(vertexArrayObject));

	//Create Vertex Buffer
    glGenBuffers(1, &buffer);

	// Generate a buffer for the indices
    glGenBuffers(1, &indexbuffer);

    loadShaders("../Shaders/vertex.glsl", "../Shaders/fragment.glsl");

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    //glFrontFace(GL_CCW);

	//Set Up Camera
    camera = new Camera(0, 0, 0);
    lightingDirection = glm::vec3(0, -1, 0);
}

Renderer::~Renderer()
{
	delete camera;


	glDetachShader(program, vertexShader);
	glDetachShader(program, fragmentShader);

	glDisableVertexAttribArray(0);
	glDeleteBuffers(1, &buffer);
}

void Renderer::drawTriangle(const Vec2<float>& v1, const Vec2<float>& v2, const Vec2<float>& v3)
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	float Positions[] =
	{
		v1.x, v1.y,
		v2.x, v2.y,
		v3.x, v3.y
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, Positions, GL_DYNAMIC_DRAW);

	glUseProgram(program);

	GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));
}

void Renderer::drawDrawable(Drawable* drawable)
{
    batch.draw(drawable);
}

void Renderer::drawFocus()
{
    Object focus(
		{ camera->xfocus, camera->yfocus, camera->zfocus },
		0.05,
		{ 1.0, 0.0, 0.0 });

    focus.Render(this);
}

void Renderer::reloadShaders()
{
    loadShaders("vertex.glsl","fragment.glsl");
}

void Renderer::renderPresent()
{
    float vertices[] = {
        1.0f, 1.0f,
       -1.0f, 1.0f,
       -1.0f, -1.0f,
        1.0f, 1.0f,
       -1.0f, -1.0f,
        1.0f, -1.0f
    };

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float)*12, vertices, GL_STATIC_DRAW));

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);

    GLCall(glUseProgram(program));
    bound = true;

    GLint timeID = glGetUniformLocation(program, "u_time");
    glUniform1f(timeID, time);
    GLint cpID = glGetUniformLocation(program, "u_cPos");
    glUniform3f(cpID, camera->getX(), camera->getY(), camera->getZ());
    GLint cdID = glGetUniformLocation(program, "u_cDir");
    glUniformMatrix4fv(cdID, 1, GL_FALSE, &camera->view[0][0]);

    GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
}

void Renderer::shiftCamera(float x, float y, float z)
{
    camera->shiftCamera(x, y, z);
}

void Renderer::moveCamera(float d)
{
    camera->moveCamera(d);
}

void Renderer::strafeCamera(float d)
{
    camera->strafeCamera(d);
}

void Renderer::rotateCameraPitch(float theta)
{
    camera->rotateCameraPitch(theta);
}

void Renderer::rotateCameraYaw(float theta)
{
    camera->rotateCameraYaw(theta);
}

void Renderer::updateTime(float delta)
{
    time += delta;
}

void Renderer::loadShaders(std::string vFilePath, std::string fFilePath)
{
	// Read our shaders into the appropriate buffers
	std::string vertexSource = LoadTextFile(vFilePath);
	std::string fragmentSource = LoadTextFile(fFilePath);

    if (vertexSource == ""){
        std::cout << "Vertex Shader is null" <<std::endl;
    }
    if (fragmentSource == ""){
        std::cout << "Fragment Shader is null" <<std::endl;
    }

	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	const char* source = (const char*)vertexSource.c_str();
	glShaderSource(vertexShader, 1, &source, 0);

	// Compile the vertex shader
	GLCall(glCompileShader(vertexShader));

	int isCompiled = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		int maxLength = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<char> infoLog(maxLength);
		glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

		glDeleteShader(vertexShader);

		for (char c : infoLog) {
			std::cout << c;
		}
		std::cout << "\n\n";
	}

	// Create an empty fragment shader handle
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Send the fragment shader source code to GL
	// Note that std::string's .c_str is NULL character terminated.
	source = (const char*)fragmentSource.c_str();
	glShaderSource(fragmentShader, 1, &source, 0);

	// Compile the fragment shader
	GLCall(glCompileShader(fragmentShader));
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		int maxLength = 0;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<char> infoLog(maxLength);
		glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

		glDeleteShader(fragmentShader);

		for (char c : infoLog) {
			std::cout << c;
		}
		std::cout << "\n\n";
	}

	// Now time to link them together into a program.
	// Get a program object.
    program = glCreateProgram();

	// Attach our shaders to our program
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	// Link our program
    GLCall(glLinkProgram(program));

	int isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE)
	{
		int maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<char> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

		for (char c : infoLog) {
			std::cout << c;
		}
		std::cout << "\n\n";

		// We don't need the program anymore.
		glDeleteProgram(program);
		// Don't leak shaders either.
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
}
