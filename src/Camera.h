#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera
{
public:
	float x;
	float y;
	float z;

	float roll;
	float pitch;
	float yaw;

	float xfocus;
	float yfocus;
	float zfocus;

public:
	Camera(float x, float y, float z);

	void updateOrientation();

    void shiftCamera(float x, float y, float z);
    void moveCamera(float d);
    void strafeCamera(float d);

    void rotateCameraPitch(float theta);
    void rotateCameraYaw(float theta);

    float getX(){return x;}
    float getY(){return y;}
    float getZ(){return z;}

    float getPitch(){return pitch;}
    float getYaw(){return yaw;}
    float getRoll(){return roll;}

    glm::mat4 projection;
	glm::mat4 view;
};
