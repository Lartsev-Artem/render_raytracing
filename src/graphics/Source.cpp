#include <iostream>
#include <vector>

enum e_object_type_t
{
	e_obj_type_none,
	e_obj_type_complex,
	e_obj_type_sphere,
	e_obj_type_plane,
	e_obj_type_light
};

static char buffer[5000];
char* ptr = buffer;
void add_screen(int w, int h)
{	
	ptr += sprintf(ptr, "%d,%d ", w, h);
}
void add_camera(const char* cam)
{
	ptr += sprintf(ptr, "%s ", cam);
}
void add_material(const float* material)
{
	ptr += sprintf(ptr, "%d,", e_obj_type_none);
	for (size_t i = 0; i < 8; i++)
	{
		ptr += sprintf(ptr, "%f,", material[i]);
	}	
	ptr += sprintf(ptr, "%f ", material[8]);
}
void add_sphere(const char* sphere)
{
	ptr += sprintf(ptr, "%d,%s ", e_obj_type_sphere, sphere);
}
void add_light(const char* light)
{
	ptr += sprintf(ptr, "%d,%s ", e_obj_type_light, light);
}
void add_plane(const char* plane)
{
	ptr += sprintf(ptr, "%d,%s ", e_obj_type_plane, plane);
}
void add_object(const char* object)
{
	ptr += sprintf(ptr, "%d,%s ", e_obj_type_complex, object);
}
void add_background(const char* file)
{
	ptr += sprintf(ptr, "%s ", file);
}

int traccer(const char* scr)
{		
	char buf[5000];
	sprintf(buf, "%s %s", scr, buffer);
	system(buf);
	exit(0);
	return 0;
}