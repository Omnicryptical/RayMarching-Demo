#include "Camera.h"

Camera::Camera(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;

	roll = 1;
	pitch = 0;
	yaw = 0;

	updateOrientation();

    this->projection = glm::perspective(glm::radians(50.0f), 1.0f, 0.1f, 1000.0f) * glm::mat4(1.0f);
	this->view = glm::lookAt(
        glm::vec3(0,      0,      0     ),
        glm::vec3(xfocus, yfocus, zfocus),
        glm::vec3(0,      roll,      0     )
    );
}

void Camera::updateOrientation()
{
	xfocus = x + cos(pitch)*cos(yaw);
	yfocus = y + sin(yaw);
	zfocus = z + sin(pitch)*cos(yaw);
}

void Camera::shiftCamera(float x, float y, float z)
{
    this->x += x;
    this->y += y;
    this->z += z;
    xfocus += x;
    yfocus += y;
    zfocus += z;

    view = projection * glm::lookAt(
        glm::vec3(x, y, z),
        glm::vec3(xfocus, yfocus, zfocus),
        glm::vec3(0, 1, 0)
    );
}

void Camera::moveCamera(float d)
{
    float xd = cos(pitch)*d;
    float zd = sin(pitch)*d;

    x += xd;
    z += zd;
    xfocus += xd;
    zfocus += zd;

    view = glm::lookAt(
        glm::vec3(0, 0, 0),
        glm::vec3(xfocus, yfocus, zfocus),
        glm::vec3(0, 1, 0)
    );
}

void Camera::strafeCamera(float d)
{
    float xd = cos(pitch+1.55f)*d;
    float zd = sin(pitch+1.55f)*d;

    x += xd;
    z += zd;
    xfocus += xd;
    zfocus += zd;

    view = glm::lookAt(
        glm::vec3(0, 0, 0),
        glm::vec3(xfocus, yfocus, zfocus),
        glm::vec3(0, 1, 0)
    );
}

void Camera::rotateCameraPitch(float theta)
{
    pitch += theta;

    updateOrientation();

    view = glm::lookAt(
        glm::vec3(0,      0,      0     ),
        glm::vec3(xfocus, yfocus, zfocus),
        glm::vec3(0,      roll,   0     )
    );
}

void Camera::rotateCameraYaw(float theta)
{
    if (yaw + theta > -1.55 && yaw + theta < 1.55) {
        yaw += theta;

        updateOrientation();

        view = glm::lookAt(
            glm::vec3(0, 0, 0),
            glm::vec3(xfocus, yfocus, zfocus),
            glm::vec3(0, roll, 0)
        );
    }
}
