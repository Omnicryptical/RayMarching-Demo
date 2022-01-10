#include "Batch.h"

Batch::Batch()
{
    vertices = new Vertex[150000]{Vertex()};
    indices = new unsigned int[1200000]{0};
}

void Batch::draw(Drawable *drawable)
{
    drawable->calculateRotation();
    drawable->generateVertices();
    int offset = vertexCount;
    if (vertexCount + drawable->vertexCount < 149999) {
        for (int i = 0; i < drawable->vertexCount; ++i){
            vertices[vertexCount+i] = drawable->vertices[i];
        }
        vertexCount += drawable->vertexCount;
        for (int i = 0; i < drawable->indexCount; ++i){
            if (indexCount < 1499999) indices[indexCount] = drawable->indices[i]+offset;
            ++indexCount;
        }
    }
}

void Batch::flush()
{
    delete vertices;
    delete indices;

    vertexCount = 0;
    indexCount = 0;

    vertices = new Vertex[150000]{Vertex()};
    indices = new unsigned int[1200000]{0};
}
