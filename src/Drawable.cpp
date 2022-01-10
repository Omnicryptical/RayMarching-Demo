#include "Drawable.h"

Drawable::Drawable()
{

}

Drawable Drawable::makeCube(float size, Color c)
{
    Drawable d = Drawable();

    d.vertices = new Vertex[8] {Vertex()};
    d.modelVertices = new Vertex[8] {
        Vertex({- size, - size, - size, c.r, c.g, c.b, 0.0, 0.0, 0.0, 0.0, 0.0}), // 0 ---
        Vertex({- size, - size, + size, c.r, c.g, c.b, 0.0, 1.0, 0.0, 0.0, 0.0}), // 1 --+
        Vertex({- size, + size, + size, c.r, c.g, c.b, 1.0, 1.0, 0.0, 0.0, 0.0}), // 2 -++
        Vertex({+ size, + size, - size, c.r, c.g, c.b, 1.0, 1.0, 0.0, 0.0, 0.0}), // 3 ++-
        Vertex({- size, + size, - size, c.r, c.g, c.b, 0.0, 1.0, 0.0, 0.0, 0.0}), // 4 -+-
        Vertex({+ size, - size, + size, c.r, c.g, c.b, 1.0, 1.0, 0.0, 0.0, 0.0}), // 5 +-+
        Vertex({+ size, - size, - size, c.r, c.g, c.b, 1.0, 0.0, 0.0, 0.0, 0.0}), // 6 +--
        Vertex({+ size, + size, + size, c.r, c.g, c.b, 1.0, 1.0, 0.0, 0.0, 0.0})  // 7 +++
    };
    d.vertexCount = 8;
    d.vertexSize = 8;
    d.indices = new unsigned int[36] {
        0,1,2,
        3,0,4,
        5,0,6,
        3,6,0,
        0,2,4,
        5,1,0,
        2,1,5,
        7,6,3,
        6,7,5,
        7,3,4,
        7,4,2,
        7,2,5
    };
    d.indexCount = 36;

    return d;
}

Drawable Drawable::makeRandomTriangle(float size, Color c)
{
    Drawable d = Drawable();


    d.vertices = new Vertex[6] {Vertex()};
    d.modelVertices = new Vertex[6] {
        Vertex({Die::rollFloat(-size, size), Die::rollFloat(-size, size), Die::rollFloat(-size, size), c.r, c.g, c.b, 0.0, 0.0, 0.0, 0.0, 0.0}),
        Vertex({Die::rollFloat(-size, size), Die::rollFloat(-size, size), Die::rollFloat(-size, size), c.r, c.g, c.b, 0.0, 1.0, 0.0, 0.0, 0.0}),
        Vertex({Die::rollFloat(-size, size), Die::rollFloat(-size, size), Die::rollFloat(-size, size), c.r, c.g, c.b, 1.0, 1.0, 0.0, 0.0, 0.0}),
        Vertex({Die::rollFloat(-size, size), Die::rollFloat(-size, size), Die::rollFloat(-size, size), c.r, c.g, c.b, 0.0, 0.0, 0.0, 0.0, 0.0}),
        Vertex({Die::rollFloat(-size, size), Die::rollFloat(-size, size), Die::rollFloat(-size, size), c.r, c.g, c.b, 0.0, 1.0, 0.0, 0.0, 0.0}),
        Vertex({Die::rollFloat(-size, size), Die::rollFloat(-size, size), Die::rollFloat(-size, size), c.r, c.g, c.b, 1.0, 1.0, 0.0, 0.0, 0.0})
    };
    d.vertexCount = 3;
    d.vertexSize = 11;
    d.indices = new unsigned int[6] {
        0,1,2,
        5,4,3
    };

    d.indexCount = 6;

    for(int i = 0; i < d.indexCount; i += 3){
        glm::vec3 triangleV1(d.modelVertices[d.indices[i]].x, d.modelVertices[d.indices[i]].y, d.modelVertices[d.indices[i]].z);
        glm::vec3 triangleV2(d.modelVertices[d.indices[i+1]].x, d.modelVertices[d.indices[i+1]].y, d.modelVertices[d.indices[i+1]].z);
        glm::vec3 triangleV3(d.modelVertices[d.indices[i+2]].x, d.modelVertices[d.indices[i+2]].y, d.modelVertices[d.indices[i+2]].z);
        glm::vec3 normal = glm::cross(triangleV1-triangleV2, triangleV1-triangleV3);
        d.modelVertices[d.indices[i]].nx = normal.x;
        d.modelVertices[d.indices[i]].ny = normal.y;
        d.modelVertices[d.indices[i]].nz = normal.z;
    }

    d.color = c;

    return d;
}

Drawable Drawable::makeRandomQuad(float size, Color c)
{
    Drawable d = Drawable();

    Vec3<float> p1 = {Die::rollFloat(-size, size), Die::rollFloat(-size, size), Die::rollFloat(-size, size)};
    Vec3<float> p2 = {Die::rollFloat(-size, size), Die::rollFloat(-size, size), Die::rollFloat(-size, size)};
    Vec3<float> p3 = {Die::rollFloat(-size, size), Die::rollFloat(-size, size), Die::rollFloat(-size, size)};
    Vec3<float> p4 = {Die::rollFloat(-size, size), Die::rollFloat(-size, size), Die::rollFloat(-size, size)};

    d.vertices = new Vertex[12] {Vertex()};
    d.modelVertices = new Vertex[12] {
        Vertex({p1.x, p1.y, p1.z, c.r, c.g, c.b, 0.0, 0.0, 0.0, 0.0, 0.0}),
        Vertex({p2.x, p2.y, p2.z, c.r, c.g, c.b, 0.0, 1.0, 0.0, 0.0, 0.0}),
        Vertex({p3.x, p3.y, p3.z, c.r, c.g, c.b, 1.0, 1.0, 0.0, 0.0, 0.0}),

        Vertex({p4.x, p4.y, p4.z, c.r, c.g, c.b, 1.0, 0.0, 0.0, 0.0, 0.0}),
        Vertex({p1.x, p1.y, p1.z, c.r, c.g, c.b, 0.0, 0.0, 0.0, 0.0, 0.0}),
        Vertex({p2.x, p2.y, p2.z, c.r, c.g, c.b, 0.0, 1.0, 0.0, 0.0, 0.0}),

        Vertex({p3.x, p3.y, p3.z, c.r, c.g, c.b, 1.0, 1.0, 0.0, 0.0, 0.0}),
        Vertex({p4.x, p4.y, p4.z, c.r, c.g, c.b, 1.0, 0.0, 0.0, 0.0, 0.0}),
        Vertex({p1.x, p1.y, p1.z, c.r, c.g, c.b, 0.0, 0.0, 0.0, 0.0, 0.0}),

        Vertex({p2.x, p2.y, p2.z, c.r, c.g, c.b, 0.0, 1.0, 0.0, 0.0, 0.0}),
        Vertex({p3.x, p3.y, p3.z, c.r, c.g, c.b, 1.0, 1.0, 0.0, 0.0, 0.0}),
        Vertex({p4.x, p4.y, p4.z, c.r, c.g, c.b, 1.0, 0.0, 0.0, 0.0, 0.0})
    };
    d.vertexCount = 12;
    d.vertexSize = 8;

    d.indices = new unsigned int[12] {
        0,1,2,
        3,4,5,
        6,7,8,
        9,10,11
    };
    d.indexCount = 12;

    for (int i = 0; i < d.vertexCount; ++i){
        d.centerOfMass.x += d.modelVertices[i].x;
        d.centerOfMass.y += d.modelVertices[i].y;
        d.centerOfMass.z += d.modelVertices[i].z;
    }
    d.centerOfMass /= d.vertexCount;

    for (int i = 0; i < d.indexCount; i += 3){
        glm::vec3 v1(d.modelVertices[d.indices[i]].x, d.modelVertices[d.indices[i]].y, d.modelVertices[d.indices[i]].z);
        glm::vec3 v2(d.modelVertices[d.indices[i+1]].x, d.modelVertices[d.indices[i+1]].y, d.modelVertices[d.indices[i+1]].z);
        glm::vec3 v3(d.modelVertices[d.indices[i+2]].x, d.modelVertices[d.indices[i+2]].y, d.modelVertices[d.indices[i+2]].z);
        glm::vec3 normal = glm::normalize(glm::cross(v1-v2, v1-v3));
        glm::vec3 triangleCenter = (v1+v2+v3)/3.f;
        if (glm::dot(normal, d.centerOfMass-triangleCenter) <= 0) normal *= -1;
        d.modelVertices[i].nx = normal.x;
        d.modelVertices[i].ny = normal.y;
        d.modelVertices[i].nz = normal.z;
        d.modelVertices[i+1].nx = normal.x;
        d.modelVertices[i+1].ny = normal.y;
        d.modelVertices[i+1].nz = normal.z;
        d.modelVertices[i+2].nx = normal.x;
        d.modelVertices[i+2].ny = normal.y;
        d.modelVertices[i+2].nz = normal.z;
    }

    d.color = c;

    return d;
}

void Drawable::setPosition(float x, float y, float z)
{
    this->position = Vec3<float>(x, y, z);
}

void Drawable::setPosition(Vec3<float> pos){
    setPosition(pos.x, pos.y, pos.z);
}

void Drawable::setRotation(float x, float y, float z)
{
    this->rotation = Vec3<float>(x,y,z);
}

void Drawable::setRotation(Vec3<float> rot)
{
    setRotation(rot.x, rot.y, rot.z);
}

void Drawable::generateVertices()
{
    for (unsigned int i = 0; i < vertexCount; ++i){
        glm::vec4 modelPos(modelVertices[i].x, modelVertices[i].y, modelVertices[i].z, 1.0f);
        modelPos = modelPos * rotationMatrix;

        vertices[i].x = modelPos.x+position.x;
        vertices[i].y = modelPos.y+position.y;
        vertices[i].z = modelPos.z+position.z;
        vertices[i].r = modelVertices[i].r;
        vertices[i].g = modelVertices[i].g;
        vertices[i].b = modelVertices[i].b;
        vertices[i].u = modelVertices[i].u;
        vertices[i].v = modelVertices[i].v;

        if (i%3 == 0){
            glm::vec4 normal(modelVertices[indices[i]].nx, modelVertices[indices[i]].ny, modelVertices[indices[i]].nz, 0.0f);
            normal = normal * rotationMatrix;

            vertices[indices[i]].nx = normal.x;
            vertices[indices[i]].ny = normal.y;
            vertices[indices[i]].nz = normal.z;
            vertices[indices[i+1]].nx = normal.x;
            vertices[indices[i+1]].ny = normal.y;
            vertices[indices[i+1]].nz = normal.z;
            vertices[indices[i+2]].nx = normal.x;
            vertices[indices[i+2]].ny = normal.y;
            vertices[indices[i+2]].nz = normal.z;
        }
    }
}

void Drawable::calculateRotation(){
    rotationMatrix = glm::mat4(1.0f);
    rotationMatrix = glm::rotate(rotationMatrix, rotation.x, glm::vec3(1, 0, 0));
    rotationMatrix = glm::rotate(rotationMatrix, rotation.y, glm::vec3(0, 1, 0));
    rotationMatrix = glm::rotate(rotationMatrix, rotation.z, glm::vec3(0, 0, 1));
}
