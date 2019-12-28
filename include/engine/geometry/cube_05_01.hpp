#ifndef __CUBE_05_01_H__
#define __CUBE_05_01_H__ 1

#include "geometry.hpp"

class Cube_05_01 final : public Geometry {
    public:
        Cube_05_01() = delete;
        explicit Cube_05_01(float size);

    private:
        float _size;
};
#endif