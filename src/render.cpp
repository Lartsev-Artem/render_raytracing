#include "Scene.h"
#define _USE_MATH_DEFINES
#include <math.h>

void render::gradient(Scene& sc){

    const int width = sc._screen._width;
    const int height = sc._screen._height;    

    for (size_t i = 0; i < width; i++) 
    {
        for (size_t j = 0; j < height; j++) 
        {
            sc._screen(i, j) = rgb_t(j / float(height), i / float(width), 0);
        }
    }
}

/*!
* Фиксирует геометрическое пересечение
*/
rgbf_t render::geometry(const Ray& ray, Scene& sc, const Vec2i& pix, int trace_lvl)
{    
    intersect_t inter;
    sc.find_intersect(ray, inter);

    if (inter.obj == nullptr)
    {
        return  sc._background._background_color;
    }

    return  inter.obj->get_material(inter.point).color;
}

/*!
* Диффузионное приближение. Хорошо приблежает матовые поверхности, при условии одного точечного источника
* или группы источников малой интенсивности
*/
rgbf_t render::diffusion(const Ray& ray, Scene& sc, const Vec2i& pix, int trace_lvl)
{
    intersect_t inter;
    sc.find_intersect(ray, inter);

    if (inter.obj == nullptr)
    {
        return  sc.get_background(pix.x, pix.y);
    }    

    float diffuse_coef = 0;
    for (auto& lights : sc._lights)
    {
        diffuse_coef += lights.get_intensity(inter);
    }

    return inter.obj->get_material(inter.point).color * diffuse_coef;
}

// Модель отражения Фонга.
/*
* Модель локального освещения. 
  Описывает отражение как комбинацию диффузного отражения шероховатых поверхностей с зеркальным отражением блестящих поверхностей.
  Поведение
  блестящие поверхности имеют небольшие интенсивные зеркальные блики.
  тусклые поверхности имеют большие блики, которые исчезают более постепенно. 
*/
rgbf_t render::phong_reflection(const Ray& ray, Scene& sc, const Vec2i& pix, int trace_lvl)
{
    intersect_t inter;
    sc.find_intersect(ray, inter);

    if (inter.obj == nullptr)
    {
        return  sc.get_background(pix.x, pix.y);
    }

    Material mat_loc = inter.obj->get_material(inter.point);

    float diffuse_coef = 0;
    float specular_coef = 0;
    for (auto& lights : sc._lights)
    {
        diffuse_coef += lights.get_intensity(inter);
        specular_coef += lights.get_specular(ray, inter);
    }    

    return mat_loc.color * diffuse_coef * mat_loc.albedo.diffuse
        + Vec3f(1., 1., 1.) * specular_coef * mat_loc.albedo.specular;
}

rgbf_t render::shadow_model(const Ray& ray, Scene& sc, const Vec2i& pix, int trace_lvl)
{
    intersect_t inter;
    sc.find_intersect(ray, inter);

    if (inter.obj == nullptr)
    {
        return sc.get_background(pix.x, pix.y);
    }
    Material mat_loc = inter.obj->get_material(inter.point);

    float diffuse_coef = 0;
    float specular_coef = 0;
    for (auto& lights : sc._lights)
    {
        if (!check_shadow(ray, inter, sc, lights))
        {
            diffuse_coef += lights.get_intensity(inter);
            specular_coef += lights.get_specular(ray, inter);
        }
    }
 
    return mat_loc.color * diffuse_coef * mat_loc.albedo.diffuse
        + Vec3f(1., 1., 1.) * specular_coef * mat_loc.albedo.specular;
}

/*многоуровневое переотражение*/
rgbf_t render::trace_reflection(const Ray& ray, Scene& sc,const Vec2i& pix, int trace_lvl)
{
    intersect_t inter;
    sc.find_intersect(ray, inter);

    if (inter.obj == nullptr || trace_lvl > depth_reflection)
    {
        return  sc.get_background(pix.x, pix.y);
    }

    Material mat_loc = inter.obj->get_material(inter.point);

    Vec3f reflect_dir = get_reflect_dir(ray.dir, inter.normal).normalize();
    point_t reflect_orig = get_shift_point(reflect_dir, inter);
    rgbf_t reflect_color = trace_reflection(Ray(reflect_orig, reflect_dir), sc, pix, trace_lvl + 1);

    float diffuse_coef = 0;
    float specular_coef = 0;
    for (auto& lights : sc._lights)
    {
        if (!check_shadow(ray, inter, sc, lights))
        {
            diffuse_coef += lights.get_intensity(inter);
            specular_coef += lights.get_specular(ray, inter);
        }
    }

    return mat_loc.color * diffuse_coef * mat_loc.albedo.diffuse
        + Vec3f(1., 1., 1.) * specular_coef * mat_loc.albedo.specular
        + reflect_color * mat_loc.albedo.absorption;   
}

/*модель с преломлением*/
rgbf_t render::snell_refraction(const Ray& ray, Scene& sc, const Vec2i& pix, int trace_lvl)
{
    intersect_t inter;
    sc.find_intersect(ray, inter);
    
    if (inter.obj == nullptr || trace_lvl > depth_reflection)
    {
        return  sc.get_background(pix.x, pix.y);
    }

    Material mat_loc = inter.obj->get_material(inter.point);

    Vec3f reflect_dir = get_reflect_dir(ray.dir, inter.normal).normalize();
    point_t reflect_orig = get_shift_point(reflect_dir, inter);        

    Vec3f refract_dir = get_refract_dir(ray.dir, inter.normal, mat_loc.refraction).normalize();
    point_t refract_orig = get_shift_point(refract_dir, inter);        

    rgbf_t reflect_color = snell_refraction(Ray(reflect_orig, reflect_dir), sc, pix, trace_lvl + 1);
    rgbf_t refract_color = snell_refraction(Ray(refract_orig, refract_dir), sc, pix, trace_lvl + 1);

    float diffuse_coef = 0;
    float specular_coef = 0;
    for (auto& lights : sc._lights)
    {
        if (!check_shadow(ray, inter, sc, lights))
        {
            diffuse_coef += lights.get_intensity(inter);
            specular_coef += lights.get_specular(ray, inter);
        }
    }

    return mat_loc.color * diffuse_coef * mat_loc.albedo.diffuse
        + Vec3f(1., 1., 1.) * specular_coef * mat_loc.albedo.specular
        + reflect_color * mat_loc.albedo.absorption
        + refract_color * mat_loc.albedo.refraction;        
}

/*проверка условия затенения*/
bool render::check_shadow(const Ray& ray, const intersect_t& p, Scene& sc, Light& src)
{
    Vec3f light_dir = src.get_light_dir(p.point);
    float light_dist = light_dir.norm();
    light_dir.normalize();

    //сдвигаем точку с объекта в направлении нормали(чтобы она не лежала на текущем объекте)
    point_t shadow_orig = get_shift_point(light_dir, p);

    intersect_t intet_obj;
    float dist = sc.find_intersect(Ray(shadow_orig, light_dir), intet_obj); //определяем пересечения с объектами сцены

    return ((dist > 0 && (intet_obj.point - shadow_orig).norm() < light_dist));
}