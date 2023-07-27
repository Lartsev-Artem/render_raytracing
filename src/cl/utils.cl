#include "Objects.cl"

typedef struct _Vector3u
{    
    uchar x, y, z;
}Vec3u;
typedef struct _Screen
{    
    int x, y;
    Vec3u* data;
}cl_screen;

typedef struct _ComplexObj
{	
	cl_Material material;

    int sv;	
    int sf;
	int sn;

    float3* _verts;  //вершины сетки
    cl_cell_t* _faces;    // треугольники. Заданы номерами вершин
    float3* _normals;    // нормали к ячейке
}complex_obj_t;

typedef struct _Ray2
{
    float3 orig; // начало луча
    float3 dir;  // направление(нормированное)
}ray_t;
typedef struct _intersect_t2
{
    int obj_id;  // объект
	int id_cell;
    float3 p;  // точка пересечния луча и объекта
    float3 normal; // нормаль к поверхности 
	int offset;
	float dist;
}cl_inter_t;

typedef struct _Camera
{
    float3 pos;
    float3 Basis[3];
    float death;
}cl_camera_t;

float norm(float3 a) { return  sqrt(a.x* a.x + a.y * a.y + a.z * a.z); }
float normV(Vec3 a) { return sqrt(a.x* a.x + a.y * a.y + a.z * a.z); }
float dot(Vec3 a, Vec3 b) { return  a.x* b.x + a.y * b.y + a.z * b.z; }
void normalize(__global Vec3* a) { 
	float n = sqrt(a->x * a->x + a->y * a->y + a->z * a->z);
	a->x /= n;
	a->y /= n;
	a->z /= n;
}

int test(int n)
{
	if(n <= 1) return 1;
	return n*test(n-1);
}

void shift_obj_ptr(__global complex_obj_t* obj)
{
	float3* p = obj->_verts;
	cl_cell_t* f = p+obj->sv;
	float3* n = f + obj->sf;

	obj->_faces = f;
	obj->_normals = n;
}

float3 get_shift_point(float3 light_dir, cl_inter_t* p_surf)
{
    float shift = 1e-3;
	float d = dot(light_dir, p_surf->normal);
    if (d < 0)
    {
        return (p_surf->p - p_surf->normal * shift);
    }
    return (p_surf->p + p_surf->normal); // * shift);	
}

float3 get_reflect_dir( float3 ray_dir,  float3 normal_surface) 
{
    return (ray_dir - normal_surface) * 2.f * dot(ray_dir, normal_surface);
}

float3 get_refract_dir( float3 I,  float3 N, const float refractive_ind) 
{
	float d = dot(I, N);	
    float cosi = -max(-1.f, min(1.f, d )); //т.к. вектора нормированы
    float etai = 1;
	float etat = refractive_ind;
    float3 n = N;
    
    // инверсия для "выходящего" луча из объекта в среду
    if (cosi < 0) 
    { 
        cosi = -cosi;

		float buf = etai;
        etai = etat; 
		etat = buf;

		n = -N;
    }
    float eta = etai / etat;
    float k = 1 - eta * eta * (1 - cosi * cosi);
    
	if( k < 0) return (float3)(0,0,0);	
	return  I * eta + n * (eta * cosi - sqrt(k));   // по закону снелла
}

 Vec3u float2int(Vec3 rgb)
 {    
    Vec3u rgb_int;    
    float MAX = max(rgb.x,  max(rgb.y, rgb.z));
    if (MAX > 1)
    {
        rgb.x /= MAX;
        rgb.y /= MAX;
        rgb.z /= MAX;
    }

    rgb_int.x = (uchar)(255.f * max(0.f, min(1.f, rgb.x)));
    rgb_int.y = (uchar)(255.f * max(0.f, min(1.f, rgb.y)));
    rgb_int.z = (uchar)(255.f * max(0.f, min(1.f, rgb.z)));

    return rgb_int;
}

float3 mult3(__global float3* lhs,const float3 rhs)
{
    float3 ret;
    ret.x = dot(lhs[0], rhs);
    ret.y = dot(lhs[1], rhs);
    ret.z = dot(lhs[2], rhs);
    return ret;
}
ray_t get_ray_view(__global cl_camera_t* cam, const float3 pixel_p)
{
    ray_t ray;
    float3 glb_start_ray = mult3(cam->Basis, pixel_p) + cam->pos; //координты начала луча в глобальных координатах    

    float3 n = (float3)(cam->Basis[0].z,cam->Basis[1].z,cam->Basis[2].z);
    if (cam->pos[1] > 0)
    {
        ray.dir = (cam->pos - (glb_start_ray + n * cam->death));
    }
    else
    {
        ray.dir = ((glb_start_ray + n * cam->death) - cam->pos);
    }

    ray.dir = normalize(ray.dir);
    ray.orig = cam->pos;
    return ray;
}