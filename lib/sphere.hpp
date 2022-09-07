#ifndef SPHERE_H
#define SPHERE_H

#include "color.hpp"
#include "point.hpp"

struct Sphere {
    Point _center;
    double _radius;
    Color _color, _k_a, _k_d, _k_s; 
    double _alpha;

    Sphere() {
        
    }

    Sphere(Point center, double radius, Color color, Color k_a, Color k_d, Color k_s, double alpha) {
        _center = center; _radius = radius; _color = color; 
        _k_a = k_a; _k_d = k_d; _k_s = k_s; _alpha = alpha;
    }
};

#endif