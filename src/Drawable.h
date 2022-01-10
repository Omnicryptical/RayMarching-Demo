#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "Mathstructs.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <algorithm>
#include <iostream>
#include "Dice.h"

struct Color {
     float r;
     float g;
     float b;
};

struct Vertex {
    float x,y,z;    // Position
    float r,g,b;    // Color
    float u,v;      // Texture Coordinates
    float nx,ny,nz; // Normal
};

class Drawable
{
public:
    Vertex* modelVertices;
    Vertex* vertices;
    unsigned int vertexCount = 0;
    unsigned int vertexSize = 11;

    unsigned int* indices;
    unsigned int indexCount = 0;

    Vec3<float> position;
    Vec3<float> rotation;
    glm::mat4 rotationMatrix;
    Color color;

    float size = 1;
    glm::vec3 centerOfMass; // Used for procedural calculation of normals

    Drawable();

    static Drawable makeRandomTriangle(float size, Color c);
    static Drawable makeRandomQuad(float size, Color c);
    static Drawable makeCube(float size, Color c);

    void setPosition(float x, float y, float z);
    void setPosition(Vec3<float> pos);

    void setRotation(float x, float y, float z);
    void setRotation(Vec3<float> rot);

    void generateVertices();
    void calculateRotation();
};

#endif // DRAWABLE_H
