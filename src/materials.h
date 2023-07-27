#ifndef MATERIALS_H
#define MATERIALS_H

#include "types.h"

struct albedo_t
{    
    float diffuse;     // коэффициент диффузионного отражения (достаточен для матовых поверхностей)
    float specular;    // коэффициент зеркального отражения (модель фонга)
    float absorption;  // коэффициент поглащения (обратный)
    float refraction;  // коэффициент преломления

    constexpr albedo_t(const float k_d = 1, const float k_s = 0, const float k_abs = 0, const float k_refr = 0) 
        :diffuse(k_d), specular(k_s), absorption(k_abs), refraction(k_refr) {};    

    albedo_t(const albedo_t& alb) { *this = alb; }
};

struct Material
{    
    albedo_t albedo;
    rgbf_t color;            // цвет тела        
    float shininess;        // постоянная блеска
    float refraction;       // коэффициент преломления
    
    constexpr Material(const albedo_t& a = albedo_t(1,0,0,0), const rgbf_t& color_obj = rgbf_t(0,0,0), const float spec = 0, const float ref = 1)
    : albedo(a.diffuse, a.specular, a.absorption, a.refraction), color(color_obj), shininess(spec), refraction(ref) {}
};

namespace material 
{    
    constexpr Material ivory(albedo_t(0.6, 0.3, 0.1, 0.0), rgbf_t( 0.4f, 0.4f, 0.3f ), 50., 1.0);
    constexpr Material red_rubber(albedo_t(0.9, 0.1, 0.0, 0.0), rgbf_t(0.3, 0.1, 0.1), 30., 1.0);
    constexpr Material green_rubber(albedo_t(0.9, 0.15, 0.0, 0.0), rgbf_t(0.1, 0.5, 0.0), 10., 1.0);
    constexpr Material glass(albedo_t(0.0, 0.5, 0.1, 0.8), rgbf_t(0.6, 0.7, 0.8), 125., 1.5);
    constexpr Material mirror(albedo_t(0.0, 10.0, 0.8, 0.0), rgbf_t(1.0, 1.0, 1.0), 1425., 1.0);
}

#endif //MATERIALS_H
