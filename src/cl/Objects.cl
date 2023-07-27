#ifndef CL_OBGECTS
#define CL_OBGECTS

typedef struct _Vector3
{    
    float x, y, z;
}Vec3;

typedef struct _cl_albedo_t
{
    float diffuse;     // коэффициент диффузионного отражения (достаточен для матовых поверхностей)
    float specular;    // коэффициент зеркального отражения (модель фонга)
    float absorption;  // коэффициент поглащения (обратный)
    float refraction;  // коэффициент преломления
}cl_albedo_t;

typedef struct _Material
{
    cl_albedo_t albedo;
    float color[3];            // цвет тела        
    float shininess;        // постоянная блеска
    float refraction;       // коэффициент преломления
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
    int obj_id;  // объект
    Vec3 p;  // точка пересечния луча и объекта
    Vec3 normal; // нормаль к поверхности    
}cl_intersect_t;

typedef struct _Ray
{
    Vec3 orig; // начало луча
    Vec3 dir;  // направление(нормированное)
}cl_ray_t;

typedef struct _Light
{
    Vec3  position;    //положение источника света
    float intensity;    // мощность источника
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
