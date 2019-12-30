#include "engine/geometry/quad_05_04.hpp"

Quad_05_04::Quad_05_04(float size) : _size(size) {
    _nVertices = 1 * 2 * 3;  //1 face * 2 triangles * 3 vertices
    _nElements = _nVertices;

    float positions[] = {  size, 0.0f, -size,
						   size, 0.0f,  size,    //upper right triangle
                          -size, 0.0f, -size,
                           

						   size, 0.0f,  size,   //lower left triangle
                          -size, 0.0f, -size,
                          -size, 0.0f,  size };

    float uvs[] = { 1.0f, 1.0f,
                    1.0f, 0.0f,
                    0.0f, 1.0f,

                    1.0f, 0.0f,
                    0.0f, 1.0f,
                    0.0f, 0.0f };

    float normals[] = { 0.0f, 1.0f, 0.0f,
                        0.0f, 1.0f, 0.0f,
                        0.0f, 1.0f, 0.0f,

                        0.0f, 1.0f, 0.0f,
                        0.0f, 1.0f, 0.0f,
                        0.0f, 1.0f, 0.0f };

    uint32_t indices[] = { 0, 2, 1,
                           3, 4, 5};

    uploadData(positions, uvs, normals, indices);
}