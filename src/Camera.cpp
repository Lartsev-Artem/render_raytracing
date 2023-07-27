#include "Camera.h"

Camera::Camera(const point_t& position) : _pos(position),  _death(400) 
{ 
    _spherical_pos = cartesian_to_sphere(_pos); 
    _pos = sphere_to_cartesian(_spherical_pos);
    _basis = SetBasis(_center_view - _pos);
}
Camera::Camera(const point_t& position,  float death) : _pos(position), _death(death) 
{
    _spherical_pos = cartesian_to_sphere(_pos);    
    _pos = sphere_to_cartesian(_spherical_pos);
    _basis = SetBasis(_center_view - _pos);
}
Camera::Camera(const Camera& cam)
{
    _pos = cam._pos;    
    _death = cam._death;
    _basis = cam._basis;
    _spherical_pos = cam._spherical_pos;
}
void Camera::move(int d_r, int d_theta, int d_phi)
{
    _spherical_pos.x += (_step_radius * d_r);
    _spherical_pos.y += (_step_angle * d_theta);
    _spherical_pos.z += (_step_angle * d_phi);

    _pos = sphere_to_cartesian(_spherical_pos);
    _basis = SetBasis(_center_view - _pos);
}

//! pixel_p- положение точки на картиной плоскости в координатах пикселей
Ray Camera::get_ray(const point_t& pixel_p)
{
    Ray ray;
    point_t glb_start_ray = _basis * pixel_p + _pos; //координты начала луча в глобальных координатах    

    Vec3f n(_basis(0, 2), _basis(1, 2), _basis(2, 2));// нормаль к картинной плоскости   
    if (_pos[1] > 0)
    {
        ray.dir = (_pos - (glb_start_ray + n * _death));
    }
    else
    {
        ray.dir = ((glb_start_ray + n * _death) - _pos);        
    }

    ray.dir.normalize();
    ray.orig = _pos;
    return ray;
}

#include "CL/opencl.h"
int Camera::to_cl(void*& data)  const
{
    struct cl_camera
    {
        cl_float3 pos;
        cl_float3 Basis[3];
        float death;
    }buf;

    data = malloc(sizeof(cl_camera));

    buf.pos.x = _pos.x;
    buf.pos.y = _pos.y;
    buf.pos.z = _pos.z;

    for (size_t i = 0; i < 3; i++)
    {
        buf.Basis[i].x = _basis(i, 0);
        buf.Basis[i].y = _basis(i, 1);
        buf.Basis[i].z = _basis(i, 2);
    }
    buf.death = _death;

    memcpy(data, &buf, sizeof(cl_camera));

    return sizeof(cl_camera);
}