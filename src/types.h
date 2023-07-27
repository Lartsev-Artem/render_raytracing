#ifndef TYPES_H
#define TYPES_H
#include "geometry.h"

typedef vec<2, int  > Vec2i;
typedef vec<2, float> Vec2f;
typedef vec<3, float> Vec3f;
typedef vec<3, int  > Vec3i;
typedef vec<3, uint8_t> Vec3u8;
typedef vec<4, float> Vec4f;

typedef matrix<3, float> Mat3f;

typedef Vec3f point_t;
typedef Vec3f rgbf_t;
typedef Vec3u8 rgb_t;
typedef Vec3i cell_t;


#endif //TYPES_H
