#ifndef SPACPP_VEC2_H
#define SPACPP_VEC2_H

#define _USE_MATH_DEFINES

#include <cmath>

namespace spacpp {
    template<class T>
    class vec2 {
    public:
        T x, y;

        vec2() : x(0), y(0) {}

        vec2(T x, T y) : x(x), y(y) {}

        vec2(const vec2 &v) : x(v.x), y(v.y) {}

        vec2 &operator=(const vec2 &v) {
            x = v.x;
            y = v.y;
            return *this;
        }

        vec2 operator+(const vec2 &v) const {
            return vec2(x + v.x, y + v.y);
        }

        vec2 operator-(const vec2 &v) const {
            return vec2(x - v.x, y - v.y);
        }

        vec2 &operator+=(const vec2 &v) {
            x += v.x;
            y += v.y;
            return *this;
        }

        vec2 &operator-=(const vec2 &v) {
            x -= v.x;
            y -= v.y;
            return *this;
        }

        vec2 operator+(T s) const {
            return vec2(x + s, y + s);
        }

        vec2 operator-(T s) const {
            return vec2(x - s, y - s);
        }

        vec2 operator*(T s) const {
            return vec2(x * s, y * s);
        }

        vec2 operator/(T s) const {
            return vec2(x / s, y / s);
        }


        vec2 &operator+=(T s) {
            x += s;
            y += s;
            return *this;
        }

        vec2 &operator-=(T s) {
            x -= s;
            y -= s;
            return *this;
        }

        vec2 &operator*=(T s) {
            x *= s;
            y *= s;
            return *this;
        }

        vec2 &operator/=(T s) {
            x /= s;
            y /= s;
            return *this;
        }

        void set(T x, T y) {
            this->x = x;
            this->y = y;
        }

        vec2 rotate(T deg) {
            T theta = deg / 180.0 * M_PI;
            T c = cos(theta);
            T s = sin(theta);
            T tx = x * c - y * s;
            T ty = x * s + y * c;
            return vec2(tx, ty);
        }

        vec2 normalize() const {
            if (length() == 0) return *this;
            return this * (1.0 / length());
        }

        float dist(const vec2 &v) const {
            vec2 d(v.x - x, v.y - y);
            return d.length();
        }

        float length() const {
            return std::sqrt(x * x + y * y);
        }

        vec2 truncate(T length) const {
            T angle = atan2f(y, x);
            return vec2(length * cos(angle), length * sin(angle));
        }

        vec2 ortho() const {
            return vec2(y, -x);
        }

        static float dot(const vec2 &v1, const vec2 &v2) {
            return v1.x * v2.x + v1.y * v2.y;
        }

        static float cross(const vec2 &v1, const vec2 &v2) {
            return (v1.x * v2.y) - (v1.y * v2.x);
        }

    };

    typedef vec2<float> vec2f;
    typedef vec2<double> vec2d;

}
#endif //SPACPP_VEC2_H