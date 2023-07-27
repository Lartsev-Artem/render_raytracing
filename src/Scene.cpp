#include "Scene.h"
#include <vector>

#define _USE_MATH_DEFINES
#include <math.h>


static std::vector<Sphere> Sphere_saved;
static std::vector<Plane> Plane_saved;
static std::vector<ComplexObj> ComplexObj_saved;

const rgb_t& Screen::operator()(const int i, const int j) const { return _pixels[i + _width * j];}
rgb_t& Screen::operator()(const int i, const int j) { return _pixels[i + _width * j];}
rgbf_t Scene::get_background(uint32_t i, uint32_t j)
{
    if (i < _background._width && j < _background._height)
    {
        return rgbf_t(
            (float)_background(i, j).x / 255,
            (float)_background(i, j).y / 255, 
            (float)_background(i, j).z / 255 );
    }
    return _background._background_color;
}

void Scene::add_light(const Light& source) {
	_lights.push_back(source);
}
void Scene::add_sphere(const Sphere& obj) {    
	Sphere_saved.push_back(obj);    
    _objects.push_back(std::make_unique<Sphere>(Sphere_saved.back()));    
}
void Scene::add_plane(const Plane& obj) {
	Plane_saved.push_back(obj);
    _objects.push_back(std::make_unique<Plane>(Plane_saved.back()));
}
void Scene::add_complex_obj(const ComplexObj& obj)
{
    ComplexObj_saved.push_back(obj);
    ComplexObj_saved.back().read_from_file();
    ComplexObj_saved.back().calculate_normals();    
        
    _objects.push_back(std::make_unique<ComplexObj>(std::move(ComplexObj_saved.back())));
}

Scene::~Scene()
{
	Plane_saved.clear();
	Sphere_saved.clear();
    ComplexObj_saved.clear();
	_lights.clear();
	_objects.clear();
}

void Scene::render(std::function<rgbf_t(const Ray&, Scene&, const Vec2i&, int)> func)
{       
    const int width = _screen._width;
    const int height = _screen._height;  

#pragma omp parallel for
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            point_t pixel_coord = 
            {
                -(float)(width / 2) + i,  //(i + 0.5);
                -(float)(height / 2) + j, //(j + 0.5);
                 0
            };
            Ray ray = _camera.get_ray(pixel_coord);
           
            _screen(i, j) = float2int(func(ray, *this, Vec2i(i, j), 0));            
        }
    }
}

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

rgb_t Scene::float2int(rgbf_t rgb)
{    
    rgb_t rgb_int;
    float max = std::max(rgb[0], std::max(rgb[1], rgb[2]));
    if (max > 1) rgb = rgb * (1. / max);
    for (size_t j = 0; j < 3; j++)
    {
        rgb_int[j] = (uint8_t)(255 * std::max(0.f, std::min(1.f, rgb[j])));
    }
    return rgb_int;
}
void Scene::output(const std::string& file, int quality)
{    
    stbi_write_jpg(file.c_str(), _screen._width, _screen._height, 3, _screen.data(), quality);
    //stbi_write_png(file.c_str(), _screen._width, _screen._height, 3, rgb.data(), 0);
}

void Scene::load_background(const std::string& file)
{
    int n = 0;
    int w, h;
    unsigned char* pixmap = stbi_load(file.c_str(), &w, &h, &n, 0);
    if (!pixmap || 3 != n) {
        std::cerr << "Error: can not load the background from " << file << std::endl;
        return;
    }
    _background.resize(w * h);
    _background._width = w;
    _background._height = h;

    for (int j = h - 1; j >= 0; j--) {
        for (int i = 0; i < w; i++) {
            _background(i, j) =
                rgb_t(pixmap[(i + j * w) * 3 + 0],
                    pixmap[(i + j * w) * 3 + 1],
                    pixmap[(i + j * w) * 3 + 2]); // *(1 / 255.);
        }
    }
    stbi_image_free(pixmap);
}

float Scene::find_intersect(const Ray& ray, intersect_t& cross)
{
    int idx = -1;
    float dist_close_obj = std::numeric_limits<float>::max(); //расстояние до ближайшего объекта    

    for (int i = 0; i < _objects.size(); i++)
    {
        float dist_i;        
        if (_objects[i]->check_intersect(ray, dist_i) && dist_i < dist_close_obj)
        {
            dist_close_obj = dist_i;
            idx = i;
        }
    }
    
    if (idx < 0)
    {
        cross.obj = nullptr;
        return -1.f;
    }

    _objects[idx]->get_intersect_obj(ray, dist_close_obj, cross);
    cross.obj = _objects[idx].get();    
    return dist_close_obj;
}