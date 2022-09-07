#ifndef IMAGE_H
#define IMAGE_H

#include <fstream>
#include <vector>
#include <array>
#include <string>
#include <iostream>

#include "color.hpp"
#include "point.hpp"
#include "vector3d.hpp"
#include "ray.hpp"

class Image {
    private:
        std::string _name;
        int _dimx, _dimy;
        std::vector<std::vector<Color>> _data;
        Point _x1, _x2, _x3, _x4, _camera;

    public:
        Image() {
            _name = ""; _dimx = 0; _dimy = 0; _data = {{}};
        }

        Image(int x, int y, std::string name) {
            _name = name;
            _dimx = x; _dimy = y;
            _data.assign(y, std::vector<Color>(x, Color(0,0,0)));

            double ratio = (double)y/(double)x;
            _x1.assign(-1,ratio,0);
            _x2.assign(1,ratio,0);
            _x3.assign(-1,-ratio,0);
            _x4.assign(1,-ratio,0);
            _camera.assign(0,0,-1);
        }

        int get_dimx() { return _dimx; }
        int get_dimy() { return _dimy; }
        Point get_camera() { return _camera; }

        bool set_pixel(int x, int y, Color color) {
            if (x < 0 || y < 0 || x >= _dimx || y >= _dimy) return false;
            _data[y][x] = color;
            return true;
        }

        bool cast_ray(int x, int y, Ray& ray) {
            if (x < 0 || y < 0 || x >= _dimx || y >= _dimy) return false;

            double alpha = ( (double) x ) / ((double) _dimx);
            double beta = ( (double) y) / ((double) _dimy);
            Point _t = _x1*(1-alpha) + _x2*alpha;
            Point _b = _x3*(1-alpha) + _x4*alpha;
            Point _p = _t*(1-beta) + _b*beta;
            ray._origin = Point(_p._x, _p._y, _p._z);
            ray._dir = _p - _camera;
            return true;
        }

        void print_image() {
            std::ofstream image(_name + ".ppm");
            image << "P3" << std::endl;
            image << _dimx << " " << _dimy << std::endl;
            image << "255" << std::endl;

            for (auto row : _data) {
                for (auto color: row) {
                    image << 255 * color._r << " " << 255 * color._g << " " << 255 * color._b << " ";
                    image << std::endl;
                }
            }

            image.close();
        }
};

#endif