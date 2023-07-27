#ifndef CL_OBGECTS
#define CL_OBGECTS

typedef struct _Vector3
{    
    float x, y, z;
}Vec3;

typedef struct _cl_albedo_t
{
    float diffuse;     // ����������� ������������� ��������� (���������� ��� ������� ������������)
    float specular;    // ����������� ����������� ��������� (������ �����)
    float absorption;  // ����������� ���������� (��������)
    float refraction;  // ����������� �����������
}cl_albedo_t;

typedef struct _Material
{
    cl_albedo_t albedo;
    float color[3];            // ���� ����        
    float shininess;        // ���������� ������
    float refraction;       // ����������� �����������
}cl_Material;

typedef struct _Sphere
{
    cl_Material material;
    Vec3 center;
    float r;
}cl_Sphere;

typedef struct _Object
{    
    int id;
    cl_Material material;
    void* data;
}cl_Object;

typedef struct _Sphere_geo
{    
    Vec3 center;
    float r;
}cl_Sphere_geo_t;

typedef struct _intersect_t
{
    int obj_id;  // ������
    Vec3 p;  // ����� ���������� ���� � �������
    Vec3 normal; // ������� � �����������    
}cl_intersect_t;

typedef struct _Ray
{
    Vec3 orig; // ������ ����
    Vec3 dir;  // �����������(�������������)
}cl_ray_t;

typedef struct _Light
{
    Vec3  position;    //��������� ��������� �����
    float intensity;    // �������� ���������
}cl_Light;

typedef union _Array
{
    struct 
    {
        int size;
        void* values;
    };
    void* data;
}array_t;

typedef struct _CELL
{
	int v[3];
}cl_cell_t;


#endif//CL_OBGECTS
