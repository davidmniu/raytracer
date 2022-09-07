#include <iostream>
#include <fstream>
#include <cstdio>
#include <algorithm>
#include <cmath>

#include "image.hpp"
#include "sphere.hpp"
#include "scene.hpp"

void cast_ray_test() {
    int xdim = 400, ydim = 300;
    double ratio = (double) ydim / (double) xdim;
    Ray ray;
    Image testImage(xdim,ydim,"test_image");
    double lenx = 2, leny = 2*ratio;
    for (int j = 0; j < ydim; j++) {
        for (int i = 0; i < xdim; i++) {
            testImage.cast_ray(i,j,ray);
            double red = (ray._dir._x + 1) / lenx * 255;
            double green = (ray._dir._y + ratio) / leny * 255;
            testImage.set_pixel(i,j,Color(red, green, 100));
        }
    }
    testImage.print_image();
}

void basic_intersect_ray_test() {
    int xdim = 400, ydim = 300;
    Ray ray;
    Image testImage(xdim, ydim, "test_image");
    Sphere sphere(Point(0,0,1), 0.25, Color(0.5,0,0), Color(0.9,0.9,0.9), Color(0.9,0.9,0.9), Color(0.9,0.9,0.9), 1);
    for (int i = 0; i < xdim; i++) {
        for (int j = 0; j < ydim; j++) {
            testImage.cast_ray(i,j,ray);
            Vector3D _d = ray._dir, _c = ray._origin - sphere._center;
            double r = sphere._radius;

            double a = _d*_d, b = 2*(_d*_c), c = _c*_c - r*r;
            double discr = b*b - 4*a*c;

            if (discr >= 0) {
                double first = ( -b + std::sqrt(discr) ) / (2*a);
                double second = (-b - std::sqrt(discr) ) / (2*a);
                if (first >= 0 || second >= 0) {
                    testImage.set_pixel(i,j,sphere._color);
                }
            }
        }
    }
    testImage.print_image();
}

void scene_test() {
    Image test_image(400, 300, "test_image");
    Color k_a(0.9,0.9,0.9), k_d(0.9,0.9,0.9), k_s(0.9,0.9,0.9);
    double alpha = 1;
    Sphere red_sphere(Point(0,0,3), 1, Color(0.5,0,0), k_a, k_d, k_s, alpha);
    Sphere green_sphere(Point(2,0,4), 1, Color(0,0.5,0), k_a, k_d, k_s, alpha);
    Color i_d(1,1,1), i_s(1,1,1);
    Light top_right_white_light(Point(2,2,1), i_d, i_s);
    Light top_front_white_light(Point(0,0,0), i_d, i_s);
    Scene test_scene({red_sphere,green_sphere}, {top_front_white_light}, test_image);
    test_scene.draw_image();
}

int main() {
    scene_test();
    return EXIT_SUCCESS;
}