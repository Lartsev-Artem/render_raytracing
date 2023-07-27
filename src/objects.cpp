#include "objects.h"

#include <cassert>
#include <fstream>
#include <sstream>

#include <filesystem> // need -std::c++17
#include "stl_reader.h"

#include "CL/opencl.h"


bool Sphere:: check_intersect(const Ray& ray, float& dist) 
{
    Vec3f L = _center - ray.orig;
    float tca = L * ray.dir;
    float d2 = L * L - tca * tca;
    if (d2 > _radius * _radius) return false;
    float thc = sqrtf(_radius * _radius - d2);
    dist = tca - thc;
    float t1 = tca + thc;
    if (dist < 0) dist = t1;
    if (dist < 0) return false;
    return true;
}
void Sphere::get_intersect_obj(const Ray& ray, float dist, intersect_t& cross)
{   
    cross.point = ray.orig + ray.dir * dist;
    cross.normal = (cross.point - _center).normalize();   
    return;
}
uint32_t Sphere::get_data_byte_size() const
{
    return sizeof(int) + sizeof(_material) + sizeof(Sphere) - offsetof(Sphere, _center);
}
uint32_t Sphere::to_cl(void* data)
{   
    uint32_t size = get_data_byte_size();

    int id = e_sphere;
    memcpy(data, &id, sizeof(int));
    memcpy((uint8_t*)data+ sizeof(int), &_material, sizeof(_material));
    memcpy((uint8_t*)data+ sizeof(_material)+ sizeof(int), &_center, sizeof(Sphere)  - offsetof(Sphere, _center));
    return size;
}

bool Plane::check_intersect(const Ray& ray, float& dist) 
{    
    if (fabs(ray.dir.y) > 1e-3) 
    {
        float y = (_p1.y + _p2.y) / 2;
        float d = -(ray.orig.y + y) / ray.dir.y; // the checkerboard plane has equation y = -4
        Vec3f pt = ray.orig + ray.dir * d;
        if (d > 0 && (pt.x > _p1.x && pt.x < _p2.x) && (pt.z > _p1.z && pt.z<_p2.z ))
        {
            dist = d;
            return true;
        }
    }
    return false;
}
void Plane::get_intersect_obj(const Ray& ray, const float dist, intersect_t& cross) /*const*/
{       
    cross.point = ray.orig + ray.dir * dist;
    cross.normal = Vec3f(0, 1, 0);    
    return;
}
const Material Plane::get_material(const Vec3f& p) const
{
    Material m = _material;
    m.color = (int(.5 * p.x + 1000) + int(.5 * p.z)) & 1 ? Vec3f(.3, .3, .3) : Vec3f(.3, .2, .1);
    return m;
}

ComplexObj::ComplexObj(const ComplexObj&& obj) noexcept
{        
    _file_grid = obj._file_grid;
    _rotate = obj._rotate;
    _disp = obj._disp;
    _collider = obj._collider;
    _material = obj._material;

    _verts = std::move(obj._verts);
    _faces = std::move(obj._faces);
    _normals = std::move(obj._normals);
    _selected_face = std::move(obj._selected_face);
}

int ComplexObj::read_from_file() 
{
    const std::filesystem::path ext = std::filesystem::path(_file_grid).extension();

    if (strcmp(ext.string().c_str(), ".obj") == 0) read_from_obj(_file_grid);
    else if (strcmp(ext.string().c_str(), ".stl") == 0) read_from_stl(_file_grid);
    else
    {
        printf("Error: function %s(). unknown format grid.  %s %d\n", __FUNCTION__, __FILE__, __LINE__);
        exit(1);
    }

    
    for (auto& p : _verts)
    {      
        p = Mat3f::RotateX(_rotate.x) * p;
        p = Mat3f::RotateY(_rotate.y) * p;
        p = Mat3f::RotateZ(_rotate.z) * p;
        
        p = p + _disp;
    }

    _collider.make_box(*this);
}
int ComplexObj::read_from_stl(const std::string& file) {
    
    stl_reader::StlMesh <float, uint32_t> mesh(file);
    _faces.resize(mesh.num_tris());
    _normals.resize(mesh.num_tris());
    _verts.resize(mesh.num_vrts());

    for (size_t iver = 0; iver < mesh.num_vrts(); ++iver)
    {
        const float* c = mesh.vrt_coords(iver);
        _verts[iver] = point_t(c[0], c[1], c[2]);
    }

    for (size_t itri = 0; itri < mesh.num_tris(); ++itri)
    {
        const uint32_t* inds = mesh.tri_corner_inds(itri);
        _faces[itri] = cell_t(inds[0], inds[1], inds[2]);

        const float* n = mesh.tri_normal(itri);
        _normals[itri] = Vec3f(n[0], n[1], n[2]);        
    }
    return 0;
}
int ComplexObj::read_from_obj(const std::string& file) {
    std::ifstream in;
    in.open(file, std::ifstream::in);
    if (in.fail()) {
        std::cerr << "Failed to open " << file << std::endl;
        return 1;
    }
    std::string line;
    while (!in.eof()) {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v ")) {
            iss >> trash;
            Vec3f v;
            for (int i = 0; i < 3; i++) iss >> v[i];
            _verts.push_back(v);
        }
        else if (!line.compare(0, 2, "f ")) {
            Vec3i f;
            int idx, cnt = 0;
            iss >> trash;
            while (iss >> idx) {
                idx--; // in wavefront obj all indices start at 1, not zero
                f[cnt++] = idx;
            }
            if (3 == cnt) _faces.push_back(f);
        }
    }    

    _normals.resize(_faces.size());    
    std::cerr << "# v# " << _verts.size() << " f# " << _faces.size() << std::endl;    
    return 0;
}

#include "omp.h"
// Moller and Trumbore
bool ComplexObj::check_intersect(const Ray& ray, float& dist) {
  
    if (!_collider.check_intersect(ray, dist))
    {
        return false;
    }
    //_selected_face = 0;
    //return true;

    dist = std::numeric_limits<float>::max();
    int fi_idx = -1;
    //_selected_face = -1;
    for (int fi = 0; fi < _faces.size(); fi++)
    {
        Vec3f edge1 = point(vert(fi, 1)) - point(vert(fi, 0));
        Vec3f edge2 = point(vert(fi, 2)) - point(vert(fi, 0));
        Vec3f pvec = cross(ray.dir, edge2);
        float det = edge1 * pvec;
        if (det < 1e-5) continue; // return false;

        Vec3f tvec = ray.orig - point(vert(fi, 0));
        float u = tvec * pvec;
        if (u < 0 || u > det)  continue; //return false;

        Vec3f qvec = cross(tvec, edge1);
        float v = ray.dir * qvec;
        if (v < 0 || u + v > det)  continue; //return false;

        float loc = edge2 * qvec * (1. / det);      

        if (loc < 1e-5) continue;

        if (loc < dist)
        {
            dist = loc;
            _selected_face[omp_get_thread_num()] = fi;
        }        
    }

    return dist > 1e-5;
}



const Vec3f& ComplexObj::point(int i) const {
    assert(i >= 0 && i < _verts.size());
    return _verts[i];
}

Vec3f& ComplexObj::point(int i) {
    assert(i >= 0 && i < _verts.size());
    return _verts[i];
}

int ComplexObj::vert(int fi, int li) const {
    assert(fi >= 0 && fi < _faces.size() && li >= 0 && li < 3);
    return _faces[fi][li];
}

void ComplexObj::get_intersect_obj(const Ray& ray, const float dist, intersect_t& cross) /*const*/
{
    cross.point = ray.orig + ray.dir * dist;
    cross.normal = _normals[_selected_face[omp_get_thread_num()]];
    if (cross.normal * ray.dir > 0) cross.normal = -cross.normal;
}

uint32_t ComplexObj::get_data_byte_size() const
{
    return sizeof(int) + sizeof(_material) +
        sizeof(int) + sizeof(cl_float3) * _verts.size() +
        sizeof(int) + sizeof(cell_t) * _faces.size() +
        sizeof(int) + sizeof(cl_float3) * _normals.size();
}
uint32_t ComplexObj::to_cl(void* data)
{    
    int id = e_complex_obj;   
    memcpy(data, &id, sizeof(int));
    int shift = sizeof(int);

    memcpy((uint8_t*)data + shift, &_material, sizeof(_material));
    shift += sizeof(_material);

    int size = _verts.size();    
    memcpy((uint8_t*)data + shift, &size, sizeof(int));
    shift += sizeof(int);

    size = _faces.size();
    memcpy((uint8_t*)data + shift, &size, sizeof(int));
    shift += sizeof(int);

    size = _normals.size();
    memcpy((uint8_t*)data + shift, &size, sizeof(int));
    shift += sizeof(int);

    for (size_t i = 0; i < _verts.size(); i++)
    {
        cl_float3 buf; 
        buf.x = _verts[i].x;
        buf.y = _verts[i].y;
        buf.z = _verts[i].z;
        memcpy((uint8_t*)data + shift, &buf, sizeof(cl_float3));       
        shift += sizeof(cl_float3);
    }    
    
    memcpy((uint8_t*)data + shift, _faces.data(), _faces.size() * sizeof(cell_t));
    shift += sizeof(cell_t) * _faces.size();
    
    for (size_t i = 0; i < _normals.size(); i++)
    {
        cl_float3 buf;
        buf.x = _normals[i].x;
        buf.y = _normals[i].y;
        buf.z = _normals[i].z;
        memcpy((uint8_t*)data + shift, &buf, sizeof(cl_float3));
        shift += sizeof(cl_float3);
    }
    return get_data_byte_size();
}

void ComplexObj::set_normal(const int fi)
{
    Vec3f edge1 = point(vert(fi, 1)) - point(vert(fi, 0));
    Vec3f edge2 = point(vert(fi, 2)) - point(vert(fi, 0));
    assert(fi < _normals.size());
    _normals[fi] = cross(edge1, edge2).normalize(); // нет проверки, внешняя эта нормаль или нет
}
void ComplexObj::calculate_normals()
{
    for (size_t fi = 0; fi <_faces.size(); ++fi)
    {
        set_normal(fi);
    }
}

void BoxCollider::make_box(const ComplexObj& obj)
{
    _min = _max = obj._verts[0];
    for (int i = 1; i < obj._verts.size(); ++i) 
    {
        for (int j = 0; j < 3; j++) 
        {
            _min[j] = std::min(_min[j], obj._verts[i][j]);
            _max[j] = std::max(_max[j], obj._verts[i][j]);
        }
    }
}

bool BoxCollider::check_intersect(const Ray& ray, float& dist)
{
    // проверяем лежит ли начальная точка внутри
    if (ray.orig[0] >= _min[0] && ray.orig[0] <= _max[0] &&
        ray.orig[1] >= _min[1] && ray.orig[1] <= _max[1] &&
        ray.orig[2] >= _min[2] && ray.orig[2] <= _max[2]) {
        return true;
    }

    // ray parameter:  x= x0 + t*dir
    float t_near = std::numeric_limits<float>::min(); //параметр ближнего пересечения
    float t_far = std::numeric_limits<float>::max();  // параметр второго пересечения
    double t1, t2;

    // directions loop
    for (int i = 0; i < 3; i++) 
    {
        if (fabs(ray.dir[i]) >= std::numeric_limits<float>::epsilon()) 
        {
            t1 = (_min[i] - ray.orig[i]) / ray.dir[i];
            t2 = (_max[i] - ray.orig[i]) / ray.dir[i];

            if (t1 > t2)
                std::swap(t1, t2);
            if (t1 > t_near)
                t_near = t1;
            if (t2 < t_far)
                t_far = t2;

            if (t_near > t_far)
                return false;
            if (t_far < 0.0)
                return false;
        } // if
        else 
        {
            if (ray.orig[i] < _min[i] || ray.orig[i] > _max[i])
                return false;
        }
    } // for

    if ((t_near <= t_far && t_far >= 0))
    {
        dist = (ray.orig + ray.dir * t_near).norm();
        return true;
    }

    return false;
}