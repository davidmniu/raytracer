#ifndef COLOR_H
#define COLOR_H

#include <iostream>

struct Color {
    double _r, _g, _b;

    Color() {
        _r = 0; _g = 0; _b = 0;
    }

    Color(double r, double g, double b) {
        _r = r, _g = g, _b = b;
    }

    Color operator+(Color other) {
        Color ans(_r+other._r, _g+other._g, _b+other._b);
        ans.cap();
        return ans;
    }

    Color operator+=(Color other) {
        _r += other._r; _g += other._g; _b += other._b;
        this->cap();
        return *this;
    }

    Color operator*(Color other) {
        Color ans(_r*other._r, _g*other._g, _b*other._b);
        ans.cap();
        return ans;
    }

    Color operator*(double val) {
        Color ans(_r*val, _g*val, _b*val);
        ans.cap();
        return ans;
    }

    void cap() {
        if (_r > 1) _r = 1;
        if (_g > 1) _g = 1;
        if (_b > 1) _b = 1;
        if (_r < 0) _r = 0;
        if (_g < 0) _g = 0;
        if (_b < 0) _b = 0;
    }

    void print() {
        std::cout << _r << ' ' << _g << ' ' << _b << std::endl;
    }
};

#endif