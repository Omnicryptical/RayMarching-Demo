#pragma once

#include "GLInclude.h"
#include "GLError.h"
#include <iostream>
#include "LoadFiles.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <vector>
#include "Camera.h"
#include <cmath>

#include "Batch.h"
#include "Drawable.h"

#include "Mathstructs.h"

class Object;

class Renderer
{
private:
	unsigned int buffer;
	unsigned int indexbuffer;
	unsigned int colorbuffer;

    unsigned int vertexArrayObject;

	unsigned int vertexShader;
	unsigned int fragmentShader;
	unsigned int program;

    unsigned char* texture0;
    int texWidth;
    int texHeight;
    int BPP;
    GLuint texNum;

    bool bound = false;

    Batch batch;

	Camera* camera;

    float time = 0.0f;
public:
    glm::vec3 lightingDirection;

	Renderer();
	~Renderer();

	void drawTriangle(const Vec2<float>& v1, const Vec2<float>& v2, const Vec2<float>& v3);
    void drawDrawable(Drawable* drawable);
	void drawFocus();

    void reloadShaders();

    void renderPresent();

	void shiftCamera(float x, float y, float z);
	void moveCamera(float d);
	void strafeCamera(float d);

	void rotateCameraPitch(float theta);
	void rotateCameraYaw(float theta);

    void updateTime(float delta);

private:
	void loadShaders(std::string vFilePath, std::string fFilePath);
};
