#ifndef LIGHT_H
#define LIGHT_H

#include "types.h"
#include "objects.h"

//! ������ ��������� ���������
class Light
{
private:
    point_t position;    //��������� ��������� �����
    float intensity;    // �������� ���������

public:
    Light() : position(0, 0, 0), intensity(0) {}
    Light(const Vec3f& p, const float& i) : position(p), intensity(i) {}
    
    Vec3f get_light_dir(const point_t& p_view) const; // ����������� ���� �� ��������� �� �����������
    float get_intensity(const intersect_t& p) const;  //������������� � ������ ���� ������
    float get_specular(const Ray& ray, const intersect_t& p) const;  // ��������� �����
};

inline Vec3f get_reflect_dir(const Vec3f& ray_dir, const Vec3f& normal_surface);    //����������� ���������
Vec3f get_refract_dir(const Vec3f& I, const Vec3f& N, const float refractive_ind);  // ����������� �����������

point_t get_shift_point(const Vec3f& light_dir, const intersect_t& p_surf); //�������� ����� ���������� � ����������� ���� � ����������� ������� �������

#endif //LIGHT_H
