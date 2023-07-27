#ifndef OBJECTS_H
#define OBJECTS_H

#include "types.h"
#include "materials.h"
#include "omp.h"

enum e_obj_type_t
{
    e_sphere = 1,
    e_plane,
    e_complex_obj,
    e_collider
};

class Object;
//! ��������� ����������� ���� � �������
struct intersect_t 
{
    Object* obj;  // ������
    point_t point;  // ����� ���������� ���� � �������
    Vec3f normal; // ������� � �����������
    intersect_t() : obj(nullptr) {};
};
struct Ray
{
    point_t orig; // ������ ����
    Vec3f dir;  // �����������(�������������)
    Ray() : orig(0, 0, 0), dir(1, 0, 0) {};
    Ray(const point_t& point, const Vec3f& direction) : orig(point), dir(direction) {};
};

class ComplexObj;
//! �������������� ���������� ������
class BoxCollider
{
private:
    point_t _min;
    point_t _max;

public:
    void make_box(const ComplexObj& obj);    
    bool check_intersect(const Ray& ray, float& dist);
};

//! ������� ����� �������������� ��������
class Object
{
protected:
    Material _material;

public:
    Object() {};
    Object(const Material& m) : _material(m) {};
    virtual bool check_intersect(const Ray& ray, float& dist) = 0; //���������� ����������� � ��������  � ���������� �� ����
    virtual void get_intersect_obj(const Ray& ray, const float dist, intersect_t& cross) = 0; //���������� ����������� � ��������  � ���������� �� ����
    virtual const Material get_material(const point_t& p) const { return _material; };  
    virtual uint32_t to_cl(void* data) { return 0; };
    virtual uint32_t get_data_byte_size() const { return 0; };
};

class Sphere : public Object 
{
protected:
    point_t _center;   // ����� �����
    float _radius;     // ������ �����
    
public:
    Sphere() : _center(0,0,0), _radius(1) {}
    Sphere(const point_t& c, const float& r) : _center(c), _radius(r) {}
    Sphere(const point_t& c, const float& r, const Material& m) : _center(c), _radius(r) { _material = m; }

    bool check_intersect(const Ray& ray, float& dist);
    void get_intersect_obj(const Ray& ray, const float dist, intersect_t& cross);

    uint32_t to_cl(void* data);
    uint32_t get_data_byte_size() const;
};

class Plane : public Object // ������ � ��������� ������������ ���
{
protected:
    point_t _p1;
    point_t _p2;

public:
    Plane() : _p1(0, 0, 0), _p2(0, 0, 0) {}
    Plane(const point_t& p1, const point_t& p2) : _p1(p1), _p2(p2) {}
    Plane(const point_t& p1, const point_t& p2, const Material& m) : _p1(p1), _p2(p2) { _material = m; }

    bool check_intersect(const Ray& ray, float& dist);
    void get_intersect_obj(const Ray& ray, const float dist, intersect_t& cross);
    const Material get_material(const point_t& p) const;
};

//! ������ � �������� ����������� ������
class ComplexObj : public Object
{
    friend class BoxCollider;
private:        
    std::string _file_grid;
    Vec3f _rotate;  // ������� ��������� ������ ������������ ���������� ���������
    point_t _disp;  // �������� ������ ���������� ����� ������ ���������������, ������������ ����� (0,0,0)
    BoxCollider _collider;

    std::vector<point_t>  _verts;  //������� �����
    std::vector<cell_t> _faces;    // ������������. ������ �������� ������
    std::vector<Vec3f> _normals;    // ������� � ������
    std::vector<int32_t> _selected_face; //��������� ������ � i-� ������
public:
    ComplexObj(const std::string& file, const Material& m, const Vec3f& rotate = Vec3f(0,0,0), const point_t& disp= point_t(0,0,0))
        : _file_grid(file), _rotate(rotate), _disp(disp) {_material = m; _selected_face.resize(omp_get_max_threads()); };

    ComplexObj(const ComplexObj& obj)
        : _file_grid(obj._file_grid), _rotate(obj._rotate), _disp(obj._disp) { _material = obj._material; _selected_face.resize(omp_get_max_threads()); };
    ComplexObj(const ComplexObj&& obj) noexcept;

    bool ray_triangle_intersect(const int& fi, const Vec3f& orig, const Vec3f& dir, float& tnear);

    const Vec3f& point(int i) const;                   // coordinates of the vertex i
    Vec3f& point(int i);                   // coordinates of the vertex i
    int vert(int fi, int li) const;              // index of the vertex for the triangle fi and local index li    

    bool check_intersect(const Ray& ray, float& dist);
    void get_intersect_obj(const Ray& ray, const float dist, intersect_t& cross);    
    int read_from_file();
    void calculate_normals();
    uint32_t get_data_byte_size() const;
    uint32_t to_cl(void* data);
private:    
    int read_from_obj(const std::string& file);
    int read_from_stl(const std::string& file);
    void set_normal(const int fi); // ������ ������� � ������ � ������� fi
};

#endif //OBJECTS_H