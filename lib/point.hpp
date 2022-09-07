#ifndef POINT_H
#define POINT_H

#include "vector3d.hpp"

struct Point {
    double _x, _y, _z;

    Point() {
        _x = 0; _y = 0; _z = 0;
    }

    Point(double x, double y, double z) {
        _x = x; _y = y; _z = z;
    }

    Point operator+(Vector3D vector) {
        return Point(_x+vector._x, _y+vector._y, _z+vector._z);
    }

    Point operator+(Point point) {
        return Point(_x+point._x, _y+point._y, _z+point._z);
    }

    Vector3D operator-(Point point) {
        return Vector3D(_x-point._x, _y-point._y, _z-point._z);
    }

    // scalar product
    Point operator*(double scalar) {
        return Point(_x * scalar, _y * scalar, _z * scalar);
    }

    void assign(double x, double y, double z) {
        _x = x; _y = y; _z = z;
    }
};

#endif