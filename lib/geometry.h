#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__
#include <cmath>
#include <vector>
#include <cassert>
#include <iostream>
#include <stdarg.h>
template <size_t DIM, typename T> struct vec {
    constexpr vec(const std::initializer_list<T> list) : data_{ 0 } { init(list); }
    vec(T X = T(), T Y = T(), T Z = T()) : data_({X,Y,Z}) {}
          T& operator[](const size_t i)       { assert(i<DIM); return data_[i]; }
    const T& operator[](const size_t i) const { assert(i<DIM); return data_[i]; }
private:
    constexpr void init(std::initializer_list<T> list) { assert(DIM == list.size()); int i = 0; for (auto el : list) data_[i++] = el; }
    T data_[DIM];
};

template <typename T> struct vec<2,T> {
    vec() : x(T()), y(T()) {}
    vec(T X, T Y) : x(X), y(Y) {}
    template <class U> vec<2,T>(const vec<2,U> &v);
          T& operator[](const size_t i)       { assert(i<2); return i<=0 ? x : y; }
    const T& operator[](const size_t i) const { assert(i<2); return i<=0 ? x : y; }
    T x,y;
};

template <typename T> struct vec<3,T> {
    //vec() : x(T()), y(T()), z(T()) {}
    constexpr vec(T X = T(), T Y = T(), T Z = T()) : x(X), y(Y), z(Z) {}
          T& operator[](const size_t i)       { assert(i<3); return i<=0 ? x : (1==i ? y : z); }
    const T& operator[](const size_t i) const { assert(i<3); return i<=0 ? x : (1==i ? y : z); }
    float norm() { return std::sqrt(x*x+y*y+z*z); }
    vec<3,T> & normalize(T l=1) { *this = (*this)*(l/norm()); return *this; }
    T x,y,z;
};

template <typename T> struct vec<4,T> {
    vec() : x(T()), y(T()), z(T()), w(T()) {}
    vec(T X, T Y, T Z, T W) : x(X), y(Y), z(Z), w(W) {}
          T& operator[](const size_t i)       { assert(i<4); return i<=0 ? x : (1==i ? y : (2==i ? z : w)); }
    const T& operator[](const size_t i) const { assert(i<4); return i<=0 ? x : (1==i ? y : (2==i ? z : w)); }
    T x,y,z,w;
};

template<size_t DIM,typename T> T operator*(const vec<DIM,T>& lhs, const vec<DIM,T>& rhs) {
    T ret = T();
    for (size_t i=DIM; i--; ret+=lhs[i]*rhs[i]);
    return ret;
}

template<size_t DIM,typename T>vec<DIM,T> operator+(vec<DIM,T> lhs, const vec<DIM,T>& rhs) {
    for (size_t i=DIM; i--; lhs[i]+=rhs[i]);
    return lhs;
}

template<size_t DIM,typename T>vec<DIM,T> operator-(vec<DIM,T> lhs, const vec<DIM,T>& rhs) {
    for (size_t i=DIM; i--; lhs[i]-=rhs[i]);
    return lhs;
}

template<size_t DIM,typename T,typename U> vec<DIM,T> operator*(const vec<DIM,T> &lhs, const U& rhs) {
    vec<DIM,T> ret;
    for (size_t i=DIM; i--; ret[i]=lhs[i]*rhs);
    return ret;
}

template<size_t DIM,typename T> vec<DIM,T> operator-(const vec<DIM,T> &lhs) {
    return lhs*T(-1);
}

template<size_t DIM, typename T> bool operator!=(const vec<DIM, T>& lhs, const vec<DIM, T>& rhs) {
    bool ret = true;
    for (size_t i = DIM; i--; ret &= (lhs[i] == rhs[i]));
    return !ret;
}

template <typename T> vec<3,T> cross(vec<3,T> v1, vec<3,T> v2) {
    return vec<3,T>(v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x);
}

template <size_t DIM, typename T> std::ostream& operator<<(std::ostream& out, const vec<DIM,T>& v) {
    for(unsigned int i=0; i<DIM; i++) {
        out << v[i] << " " ;
    }
    return out ;
}

template <size_t DIM, typename T> struct matrix {
    matrix() : data_{ 0 } {}
    matrix(std::initializer_list<T> list) : data_{ 0 } { init(list); }
   
    T& operator()(const size_t i, const size_t j) { assert(i < DIM && j <DIM); return data_[i*DIM+j]; }
    const T& operator()(const size_t i, const size_t j) const { assert(i < DIM && j<DIM); return data_[i*DIM+j]; }

    static constexpr matrix<3, T>  RotateX(T fi) {
        return matrix < 3, T>{1.f, 0.f, 0.f,
            0.f, cosf(fi), -sinf(fi),
            0.f, sinf(fi), cosf(fi)};
    };

    static constexpr matrix<3, T>  RotateY(T fi) {
        return matrix < 3, T>{ cosf(fi), 0.f, sinf(fi),
        0.f, 1.f, 0.f,
        -sinf(fi), 0.f, cosf(fi) };
    };

    static constexpr matrix<3, T>  RotateZ(T fi) {
        return matrix < 3, T>{cosf(fi), -sinf(fi), 0.f,
        sinf(fi), cosf(fi) , 0.f,
        0.f, 0.f, 1.f};
    };
   
private:
    T data_[DIM*DIM];
    constexpr void init(std::initializer_list<T> list) { assert(DIM * DIM == list.size()); int i = 0; for (auto el : list) data_[i++] = el;}
};
template<size_t DIM, typename T> vec<DIM, T> operator*(const matrix<DIM, T>& lhs, const vec<DIM, T>& rhs) {
    vec<DIM, T> ret;
    for (size_t i = 0; i < DIM; i++)
    {
        ret[i] = 0;
        for (size_t j = 0; j < DIM; j++)ret[i] += lhs(i, j) * rhs[j];
    }
    return ret;
}

//! задает базис новой системы координат с плоскостью XoY ортогональной заданному направлению
template<size_t DIM, typename T> matrix<3, T> SetBasis(const vec<DIM, T>& direction)
{
    vec<3, T> v1, v2, n = direction;
    n.normalize();
    if (fabs(n[1]) < 1e-20)
    {
        v1[0] = 0;
        v1[1] = 1;
        v1[2] = 0;
    }
    else
    {
        v1[0] = 1;
        v1[1] = -(n[0] * v1[0] + n[2] * v1[2]) / n[1];
        v1[2] = 0;
    }
    v1.normalize();

    if (n[1] < 0) n = -n;
    v2 = cross(v1, n).normalize();

    matrix<3, T> A;
    for (int i = 0; i < DIM; i++)
    {
        A(i, 0) = v1[i];
        A(i, 1) = v2[i];
        A(i, 2) = n[i];
    }

    return A;
}

#define _USE_MATH_DEFINES
#include <math.h>
template<typename T> vec<3, T> cartesian_to_sphere(const vec<3, T>& xyz, const vec<3, T>& orig = vec<3, T>(0, 0, 0))
{
    float r = (xyz - orig).norm();
    return vec<3, T>( r, acosf(xyz.z / r), atan2f(xyz.y, xyz.x) );
}
template<typename T> vec<3, T> sphere_to_cartesian( vec<3, T>& pos, const vec<3, T>& orig = vec<3, T>(0, 0, 0))
{
    T theta = pos.y + M_PI / 2;
    return vec<3, T>(    
        pos.x * sinf(theta) * cosf(pos.z) + orig.x,
        pos.x * sinf(theta) * sinf(pos.z) + orig.y,
        pos.x * cosf(theta) + orig.z
    );
}
#endif //__GEOMETRY_H__

