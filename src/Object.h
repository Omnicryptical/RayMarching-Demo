#pragma once

#include "Renderer.h"
#include "Dice.h"
#include "Drawable.h"

class Object
{
private:
public:
	Vec3<float> position;
    Vec3<float> rotation;
	float size;
    Vec3<float> speed;
    Vec3<float> angularSpeed;

    Drawable drawable;

    Object(Vec3<float> position, float size, Color color)
	{
        this->position = position;
        this->speed = {0.f,0.f,0.f};
        this->angularSpeed = {Die::rollFloat(-0.001, 0.001), Die::rollFloat(-0.001, 0.001), Die::rollFloat(-0.001, 0.001)};
        this->size = size/2;

        this->rotation = Vec3<float>(0,0,0);

        this->drawable = Drawable::makeRandomQuad(size, color);
        drawable.position = position;
        drawable.color = color;
	}

	void Render(Renderer* renderer)
	{
	}
	void Update(float delta)
    {
		position.x += speed.x*600*delta;
		position.y += speed.y*600*delta;
        position.z += speed.z*600*delta;
        rotation.x += angularSpeed.x*600*delta;
        rotation.y += angularSpeed.y*600*delta;
        rotation.z += angularSpeed.z*600*delta;

        drawable.setPosition(position);
        drawable.setRotation(rotation);
	}
};
