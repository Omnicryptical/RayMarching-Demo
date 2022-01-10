#ifndef BATCH_H
#define BATCH_H

#include "Drawable.h"
#include "Vendor/stb_image.h"

class Batch
{
public:
    Batch();

    Vertex* vertices;
    unsigned int vertexCount = 0;
    unsigned int vertexSize = 11;

    unsigned int* indices;
    unsigned int indexCount = 0;

    void draw(Drawable* drawable);

    void flush();
};

#endif // BATCH_H
