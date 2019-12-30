#ifndef __QUAD_05_04_H__
#define __QUAD_05_04_H__ 1

#include "geometry.hpp"

class Quad_05_04 final: public Geometry {
    public:
        Quad_05_04() = delete;
        explicit Quad_05_04(float size);

    private:
        float _size;
};
#endif