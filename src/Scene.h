#ifndef SCENE_H
#define SCENE_H

#include "render.h"
#include "light.h"
#include "objects.h"
#include "Camera.h"
#include <functional>

class Scene
{	
	friend class render;
	friend class render_cl;
	friend class process_sdl;

private:
	Screen _screen;
	Screen _background;
	Camera _camera;
	std::vector<Light> _lights;	
	std::vector<std::unique_ptr<Object>> _objects;

public:	

	Scene(const Vec2i& screen_size, const Camera& camera) :_screen(screen_size.x, screen_size.y), _camera(camera) {};
	~Scene();

	void add_light(const Light& source);
	void add_sphere(const Sphere& obj);
	void add_plane(const Plane& obj);	
	void add_complex_obj(const ComplexObj& obj);	

	void render(std::function<rgbf_t(const Ray&, Scene&, const Vec2i&, int)> func);
	void output(const std::string& file, int quality = 100);
	void load_background(const std::string& file);
	void output();

	inline void set_camera(const Vec3i& pos) { return _camera.move(pos.x, pos.y, pos.z); }
	inline Screen& get_screen() { return _screen; }
private:
	rgbf_t get_background(uint32_t i, uint32_t j);

	//ищет пересечения с объектом. Записывает данных пересечения. Возвращает расстояние до пересечения
	float find_intersect(const Ray& ray, intersect_t& cross); 
	rgb_t float2int(rgbf_t rgb);	
};

#endif //SCENE_H