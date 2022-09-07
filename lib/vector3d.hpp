#ifndef VECTOR_3D_H
#define VECTOR_3D_H

struct Vector3D {
    double _x, _y, _z;

    Vector3D() {
        _x = 0; _y = 0; _z = 0;
    }

    Vector3D(double x, double y, double z) {
        _x = x; _y = y; _z = z;
    }

    void assign(double x, double y, double z) {
        _x = x; _y = y; _z = z;
    }

    Vector3D operator+(Vector3D other) {
        return Vector3D(_x + other._x, _y + other._y, _z + other._z);
    }

    Vector3D operator-(Vector3D other) {
        return Vector3D(_x - other._x, _y - other._y, _z - other._z);
    }

    // scalar product
    Vector3D operator*(double scalar) {
        return Vector3D(_x * scalar, _y * scalar, _z * scalar);
    }

    // dot product
    double operator*(Vector3D other) {
        return (_x * other._x) + (_y * other._y) + (_z * other._z);
    }

    void normalize() {
        double norm = (*this)*(*this);
        if (norm) {
            _x /= norm; _y /= norm; _z /= norm;
        }
    }

    void print() {
        std::cout << _x << ' ' << _y << ' ' << _z << std::endl;
    }
};

#endif