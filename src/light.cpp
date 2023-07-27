#include "light.h"

float Light::get_intensity(const intersect_t& p) const
{
    Vec3f light_dir = (position - p.point).normalize();
    return intensity * std::max(0.f, light_dir * p.normal); //Чем меньше угол, тем лучше освещена поверхность.
}
float Light::get_specular(const Ray& ray, const intersect_t& p) const
{
    Vec3f light_dir = (position - p.point).normalize();
    return powf(std::max(0.f, -get_reflect_dir(-light_dir, p.normal) * ray.dir), p.obj->get_material(p.point).shininess) * intensity;
}

Vec3f Light::get_light_dir(const point_t& p_view) const
{
    return (position - p_view);
}

Vec3f get_reflect_dir(const Vec3f& ray_dir, const Vec3f& normal_surface) {
    return ray_dir - normal_surface * 2.f * (ray_dir * normal_surface); //по закону фонга
}

Vec3f get_refract_dir(const Vec3f& I, const Vec3f& N, const float refractive_ind) 
{
    float cosi = -std::max(-1.f, std::min(1.f, I * N)); //т.к. вектора нормированы
    float etai = 1, etat = refractive_ind;
    Vec3f n = N;
    
    // инверсия для "выходящего" луча из объекта в среду
    if (cosi < 0) 
    { 
        cosi = -cosi;
        std::swap(etai, etat); n = -N;
    }
    float eta = etai / etat;
    float k = 1 - eta * eta * (1 - cosi * cosi);
    return k < 0 ? Vec3f(0, 0, 0) : I * eta + n * (eta * cosi - sqrtf(k)); // по закону снелла
}

point_t get_shift_point(const Vec3f& light_dir, const intersect_t& p_surf)
{
    constexpr float shift = 1e-3;
    if (light_dir * p_surf.normal < 0)
    {
        return (p_surf.point - p_surf.normal * shift);
    }
    return (p_surf.point + p_surf.normal * shift);
}

//#include "Scene.h"
//bool check_shadow(const Ray& ray, const intersect_t& p, Scene& sc, Light& src)
//{
//    Vec3f light_dir = (src.position - p.point).normalize();
//    float light_distance = (src.position - p.point).norm();
//
//    //сдвигаем точку с объекта в направлении нормали(чтобы она не лежала на текущем объекте)
//    Vec3f shadow_orig = light_dir * p.normal < 0 ? p.point - p.normal * 1e-3 : p.point + p.normal * 1e-3;
//
//    intersect_t intet_obj;
//    float dist = sc.find_intersect(Ray(shadow_orig, light_dir), intet_obj);
//
//    return ((dist > 0 && (intet_obj.point - shadow_orig).norm() < light_distance));
//}