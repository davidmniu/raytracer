#ifndef RAY_H
#define RAY_H

#include "vector3d.hpp"
#include "point.hpp"

struct Ray {
    Vector3D _dir;
    Point _origin;

    Ray() {
        _dir = Vector3D();
        _origin = Point();
    }

    Ray(Vector3D dir, Point origin) {
        _dir = dir; _origin = origin;
    }
};

#endif