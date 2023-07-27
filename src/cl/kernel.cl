#include "Objects.cl"
#include "utils.cl"


__kernel void gradient(__global cl_screen* screen)
{
	int i = get_global_id(0);
	int j = get_global_id(1);

	const int width = screen->x;
	const int height = screen->y;	


	if (i >= width || j >= height)
	{ 
		return;
	}
	
	__global Vec3* data = &screen->data;	
	const int pos = (i + width * j);
	
	data[pos + 0].x =  (float)j / (float)height;
	data[pos + 0].y =  (float)i / (float)width;
	data[pos + 0].z = 0;
}

bool check_intersect_sphere(__global cl_Sphere* sphere, ray_t ray,  float* dist)
{
	*dist = 9999.0f;
	float3 L;
	L.x = sphere->center.x - ray.orig.x;
	L.y = sphere->center.y - ray.orig.y;
	L.z = sphere->center.z - ray.orig.z;

	float tca = dot(L, ray.dir);
	float d2 = dot(L, L) - tca * tca;
	if (d2 > sphere->r * sphere->r) return false;
	float thc = sqrt(sphere->r * sphere->r - d2);
	*dist = tca - thc;
	float t1 = tca + thc;
	if (*dist < 0) *dist = t1;
	if (*dist < 0) return false;
	return true;
}
void get_intersect_sphere(const ray_t ray, float dist, __global const cl_Sphere* sphere, cl_inter_t* cross)
{
	cross->p.x = ray.orig.x + ray.dir.x * dist;
	cross->p.y = ray.orig.y + ray.dir.y * dist;
	cross->p.z = ray.orig.z + ray.dir.z * dist;

	cross->normal.x = (cross->p.x - sphere->center.x);
	cross->normal.y = (cross->p.y - sphere->center.y);
	cross->normal.z = (cross->p.z - sphere->center.z);

	cross->normal = normalize(cross->normal);

	cross->dist = dist;
	return;
}


int check_intersect_complex(__global complex_obj_t* obj, ray_t ray,  float* dist)
{
	*dist = 9999.0f;
    int fi_idx = -1;

	__global float3* verts = &obj->_verts;  	
	__global cl_cell_t* faces = (verts + obj->sv);   
    __global float3* normals = faces + obj->sf;   
    int _selected_face =-1;
    
	for (int fi = 0; fi < obj->sf; fi++)
    {		
		float3 edge1 = (verts[faces[fi].v[1]] - verts[faces[fi].v[0]]);
		float3 edge2 = (verts[faces[fi].v[2]] - verts[faces[fi].v[0]]);    

         float3 pvec = cross(ray.dir, edge2);
         float det = dot(edge1 , pvec);
         if (det < 1e-5) continue; // return false;

    	 float3 tvec = ray.orig - verts[faces[fi].v[0]];
         float u = dot(tvec , pvec);
         if (u < 0 || u > det)  continue; //return false;

         float3 qvec = cross(tvec, edge1);
         float v = dot(ray.dir , qvec);
         if (v < 0 || u + v > det)  continue; //return false;

         float loc = dot(edge2 , qvec) * (1. / det);      

         if (loc < 1e-5) continue;

        if (loc < *dist)
        {
            *dist = loc;
            _selected_face = fi;
        }        
    }

	if(*dist > 1e-5) return _selected_face;
	return -1;
    //return *dist > 1e-5;
}
void get_intersect_complex(const ray_t ray, float dist, __global const complex_obj_t* obj, cl_inter_t* cross)
{
	cross->p.x = ray.orig.x + ray.dir.x * dist;
	cross->p.y = ray.orig.y + ray.dir.y * dist;
	cross->p.z = ray.orig.z + ray.dir.z * dist;

	__global float3* verts = &obj->_verts;  	
	__global cl_cell_t* faces = (verts + obj->sv);   
    __global float3* normals = faces + obj->sf;   

	cross->normal = normals[cross->id_cell];	
	cross->dist = dist;
	return;
}

int find_intersect(__global int* size, __global cl_Object* objs,  ray_t* ray, cl_inter_t* cross)
{
	int idx = -1;
	int id_obj = 0;
	int shift = 0;
	float dist_close_obj =999999.f;   
	
	__global cl_Object* obj = objs;
	__global cl_Sphere* sph;
	__global complex_obj_t* comp_obj;
	__global char* ptr0 = objs;	
	int id_face = -1;
		
	float dist_i =0;
	for (int i = 0; i < size[0]; i++)
	{						
		bool f = false;		
		__global char* ptr = obj;
		int size_byte =0;
		int id = obj->id;	
		switch(id)
		{
			case 1:
				sph = &obj->material;								
				f = check_intersect_sphere(sph, *ray, &dist_i);	
				size_byte = sizeof(int) + sizeof(cl_Sphere);					
				ptr += (size_byte);
				obj  = ptr;					
			break;

			case 3:
				comp_obj = &obj->material;								
				id_face = check_intersect_complex(comp_obj, *ray, &dist_i);	
				size_byte = 4*sizeof(int) +sizeof(cl_Material)+ comp_obj->sv*sizeof(float3) +comp_obj->sf*sizeof(cl_cell_t)
				+comp_obj->sn*sizeof(float3);					
				ptr += (size_byte);
				obj  = ptr;							
				
				if(id_face>=0) 
				{					
					f = true; 				
				}
			break;

			default:
				printf("id= %d\n", obj->id);
			break;
		}

		if (f && (dist_i < dist_close_obj))
		{
			dist_close_obj = dist_i;
			idx = i;
			cross->dist = dist_close_obj;
			shift = ptr-ptr0 - size_byte;	
			id_obj = id;			
		}
	}

	if (idx < 0)
	{
		cross->obj_id = -1;
		cross->dist = -1;
		return -1;
	}

	switch(id_obj)
	{
		case 1:
			sph = ptr0 + shift + sizeof(int);
			get_intersect_sphere(*ray, dist_close_obj, sph, cross);
		break;	
		
		case 3:
			cross->id_cell = id_face;
			comp_obj = ptr0 + shift + sizeof(int);
			get_intersect_complex(*ray, dist_close_obj, comp_obj, cross);
		break;
	}

	cross->obj_id = idx;
	return  shift;
}

bool check_shadow(__global int* size,  __global cl_Object* objs, cl_inter_t* p, float3 light_dir, float light_dist)
{
	ray_t ray;

    //сдвигаем точку с объекта в направлении нормали(чтобы она не лежала на текущем объекте)
    ray.orig = get_shift_point(light_dir, p);
	ray.dir = light_dir;
	
    cl_inter_t intet_obj;	
	int offset = find_intersect(size, objs, &ray, &intet_obj);

	float3 pp = (intet_obj.p - ray.orig);
	float norm = sqrt(pp.x*pp.x + pp.y*pp.y + pp.z*pp.z);
    return ((intet_obj.dist > 0) &&  norm < light_dist);
}

__kernel void phong_reflection( __global cl_screen* screen,__global cl_screen* background, __global int* size, 
__global cl_Object* objs, __global cl_Light* lights, __global cl_camera_t* camera
)
{		
	int i = get_global_id(0);	
	int j = get_global_id(1);

	const int width = screen->x;
	const int height = screen->y;	

	if (i >= width || j >= height)
	{
		return;
	}
	
	 float3 pixel_coord = (float3)(            
                -(float)(width / 2) + i,  //(i + 0.5);
                -(float)(height / 2) + j, //(j + 0.5);
                 0
	 );
	ray_t ray = get_ray_view(camera, pixel_coord);

	//======================================================
	Vec3u clr;
	if (i < background->x && j < background->y)
	{
		__global Vec3u* data = &background->data;
		clr = data[(i + background->x * j)];	
	}
	else
	{
		clr.x=0;
		clr.y=0;
		clr.z=0;
	}

	cl_inter_t inter;	
	int offset = find_intersect(size, objs, &ray, &inter);
		
	if (inter.obj_id >= 0)
	{								
		__global char* ptr = objs;		
		__global cl_Object* obj = ptr + offset;

		__global cl_Material* mat_loc = &obj->material;
		
		float diffuse_coef = 0;
		float specular_coef = 0;

		__global int* n = lights;			
		__global cl_Light* light = (n+1);
		
		for (int i=  0; i < *n; i++)	
		{		
			float3 light_dir;
			light_dir.x =  (light->position.x - inter.p.x);
			light_dir.y =  (light->position.y - inter.p.y);
			light_dir.z =  (light->position.z - inter.p.z);
			float norm = sqrt(light_dir.x*light_dir.x + light_dir.y*light_dir.y + light_dir.z*light_dir.z);
			light_dir = normalize(light_dir);		
			
			if(!check_shadow(size, objs, &inter,light_dir,norm))
			{			
				diffuse_coef += light->intensity * max(0.f, dot(light_dir, inter.normal)); //Чем меньше угол, тем лучше освещена поверхность.		

				float3 reflect_dir;
				float coef = -2.f * dot(light_dir, inter.normal);
				reflect_dir.x = -light_dir.x - inter.normal.x * coef;
				reflect_dir.y = -light_dir.y - inter.normal.y * coef;
				reflect_dir.z = -light_dir.z - inter.normal.z * coef;		
				specular_coef += pow( max(0.f, -dot(reflect_dir, ray.dir)), obj->material.shininess * light->intensity);
			}
			light++;
		}	


		Vec3 rgb;		
		rgb.x =  mat_loc->color[0] * diffuse_coef * mat_loc->albedo.diffuse
			+  specular_coef * mat_loc->albedo.specular;

		rgb.y =  mat_loc->color[1] * diffuse_coef * mat_loc->albedo.diffuse
			+  specular_coef * mat_loc->albedo.specular;

		rgb.z =  mat_loc->color[2] * diffuse_coef * mat_loc->albedo.diffuse
			+  specular_coef * mat_loc->albedo.specular;		
	
 		clr = float2int(rgb);

	}
	//======================================================
		
	__global Vec3u* data = &screen->data;		
	data[(i + width * j)] = clr;
}


Vec3 snell_refraction_body(__global int* size, 
__global cl_Object* objs, __global cl_Light* lights, ray_t* ray
)
{
	Vec3 clr;	
		clr.x = 0.2;
		clr.y = 0.7;
		clr.z = 0.8;	

	cl_inter_t inter;	
	int offset = find_intersect(size, objs, ray, &inter);
		
	if (inter.obj_id < 0)
	{						
		return clr;
	}
	
	__global char* ptr = objs;		
	__global cl_Object* obj = ptr + offset;

	__global cl_Material* mat_loc = &obj->material;

	 float3 reflect_dir = normalize(get_reflect_dir(ray->dir, inter.normal));
	 float3 reflect_orig = get_shift_point(reflect_dir, &inter);        

	float3 refract_dir = normalize(get_refract_dir(ray->dir, inter.normal, mat_loc->refraction));
	float3 refract_orig = get_shift_point(refract_dir, &inter);        

	ray_t reflect_ray; 
	reflect_ray.dir = reflect_dir; 
	reflect_ray.orig = reflect_orig; 
	// Vec3 reflect_color = clr;// = snell_refraction_body(size, objs, lights, &reflect_ray, lvl+1);			
	// Vec3 refract_color = clr;// = snell_refraction(Ray(refract_orig, refract_dir), sc, pix, trace_lvl + 1);

	float diffuse_coef = 0;
	float specular_coef = 0;

	__global int* n = lights;			
	__global cl_Light* light = (n+1);
	
	for (int i=  0; i < *n; i++)	
	{		
		float3 light_dir;
		light_dir.x =  (light->position.x - inter.p.x);
		light_dir.y =  (light->position.y - inter.p.y);
		light_dir.z =  (light->position.z - inter.p.z);
		float norm = sqrt(light_dir.x*light_dir.x + light_dir.y*light_dir.y + light_dir.z*light_dir.z);
		light_dir = normalize(light_dir);		
		
		//if(!check_shadow(size, objs, &inter,light_dir,norm))
		{			
			diffuse_coef += light->intensity * max(0.f, dot(light_dir, inter.normal)); //Чем меньше угол, тем лучше освещена поверхность.		

			float3 reflect_dir;
			float coef = -2.f * dot(light_dir, inter.normal);
			reflect_dir.x = -light_dir.x - inter.normal.x * coef;
			reflect_dir.y = -light_dir.y - inter.normal.y * coef;
			reflect_dir.z = -light_dir.z - inter.normal.z * coef;		
			specular_coef += pow( max(0.f, -dot(reflect_dir, ray->dir)), obj->material.shininess * light->intensity);
		}
		light++;
	}	
				
    clr.x =  mat_loc->color[0] * diffuse_coef * mat_loc->albedo.diffuse
        +  specular_coef * mat_loc->albedo.specular;

	clr.y =  mat_loc->color[1] * diffuse_coef * mat_loc->albedo.diffuse
		+  specular_coef * mat_loc->albedo.specular;

	clr.z =  mat_loc->color[2] * diffuse_coef * mat_loc->albedo.diffuse
		+  specular_coef * mat_loc->albedo.specular;
	
	return clr;
}

