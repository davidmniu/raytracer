#ifndef LIGHT_H
#define LIGHT_H

#include "point.hpp"
#include "color.hpp"

struct Light {
    Point _location;
    Color _i_d, _i_s;

    Light(Point location, Color i_d, Color i_s) {
        _location = location; _i_d = i_d; _i_s = i_s;
    }
};

#endif