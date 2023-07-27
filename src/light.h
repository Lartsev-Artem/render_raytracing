#ifndef LIGHT_H
#define LIGHT_H

#include "types.h"
#include "objects.h"

//! объект источника излучения
class Light
{
private:
    point_t position;    //положение источника света
    float intensity;    // мощность источника

public:
    Light() : position(0, 0, 0), intensity(0) {}
    Light(const Vec3f& p, const float& i) : position(p), intensity(i) {}
    
    Vec3f get_light_dir(const point_t& p_view) const; // направление луча от источника до наблюдателя
    float get_intensity(const intersect_t& p) const;  //интенсивность с учётом угла обзора
    float get_specular(const Ray& ray, const intersect_t& p) const;  // отражение Фонга
};

inline Vec3f get_reflect_dir(const Vec3f& ray_dir, const Vec3f& normal_surface);    //направление отражения
Vec3f get_refract_dir(const Vec3f& I, const Vec3f& N, const float refractive_ind);  // направление преломления

point_t get_shift_point(const Vec3f& light_dir, const intersect_t& p_surf); //сдвигает точку пересчения с поверхности тела в направлении внешней нормали

#endif //LIGHT_H
