#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <cmath>

#include "sphere.hpp"
#include "light.hpp"
#include "image.hpp"

class Scene {
    private:
        std::vector<Sphere> _spheres;
        std::vector<Light> _lights;
        Image _image;

        double intersect_t(Sphere& sphere, Ray& ray) {
            Vector3D _d = ray._dir, _c = ray._origin - sphere._center;
            double r = sphere._radius;

            double a = _d*_d, b = 2*(_d*_c), c = _c*_c - r*r;
            double discr = b*b - 4*a*c;

            double ans_t;
            if (discr >= 0) {
                double first = ( -b + std::sqrt(discr) ) / (2*a);
                double second = (-b - std::sqrt(discr) ) / (2*a);
                if (first >= 1 && second >= 1) {
                    ans_t = std::min(first,second);
                } else if (first >= 1) {
                    ans_t = first;
                } else if (second >= 1) {
                    ans_t = second;
                } else {
                    return -1;
                }
                return ans_t;
            } else {
                return -1;
            }
        }

        Color get_ambient_term(Sphere& sphere) {
            return sphere._color * sphere._k_a;
        }

        Color get_diffuse_and_specular_term(Sphere& sphere, Point& intersect, Vector3D& normal) {
            Color diffuse_total, specular_total;
            for (auto& light : _lights) {
                Vector3D light_vec = light._location - intersect;
                light_vec.normalize();
                double prod = (light_vec * normal);
                if (prod < 0) continue;
                Color diffuse_term = (sphere._k_d * light._i_d) * prod;
                diffuse_total += diffuse_term;

                Vector3D reflectance = normal * (2* prod) - light_vec;
                Vector3D view_vec = _image.get_camera() - intersect;
                view_vec.normalize();
                Color specular_term = (sphere._k_s * light._i_s) * std::pow( reflectance * view_vec, sphere._alpha );
                // std::cout << std::pow( reflectance * view_vec, sphere._alpha ) << std::endl;
                specular_total += specular_term;
            }
            // diffuse_total.print();
            return diffuse_total + specular_total;
        }
    
    public:
        Scene(std::vector<Sphere> spheres, std::vector<Light> lights, Image image) {
            _spheres = spheres; _lights = lights; _image = image;
        }

        void draw_image() {
            Ray ray;
            int dimx = _image.get_dimx(), dimy = _image.get_dimy();
            for (int i = 0; i < dimx; i++) {
                for (int j = 0; j < dimy; j++) {
                    Sphere closest_sphere;
                    Color final_color;
                    double min_t = __DBL_MAX__;
                    _image.cast_ray(i,j,ray);
                    for (auto& sphere : _spheres) {
                        double curr_t = intersect_t(sphere, ray);
                        if (curr_t != -1 && curr_t < min_t) {
                            min_t = curr_t;
                            closest_sphere = sphere;
                        }
                    }
                    if (min_t == __DBL_MAX__) continue;
                    Point intersect = ray._origin + ray._dir*min_t;
                    Vector3D normal = intersect - closest_sphere._center;
                    normal.normalize();
                    final_color += get_ambient_term(closest_sphere);
                    final_color += get_diffuse_and_specular_term(closest_sphere,intersect,normal);
                    _image.set_pixel(i,j,final_color);
                }
            }
            _image.print_image();
        }
};

#endif