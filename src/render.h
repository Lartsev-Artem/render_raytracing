#ifndef RENDER_H
#define RENDER_H

#include "types.h"
#include "objects.h"
#include "light.h"

class Scene;

struct Screen
{
	size_t _width;				 // ������ ������ � ��������
	size_t _height;				 // ������ ������ � ��������
	rgbf_t _background_color = rgbf_t(0.2, 0.7, 0.8);	// ������� ��� ������	
private:
	std::vector<rgb_t> _pixels; //�������� ����� rgb � ������ ������� (��������� ���������).	
public:

	Screen(const int w = 0, const int h = 0) : _width(w), _height(h) { _pixels.resize(w * h); }
	const rgb_t& operator()(const int i, const int j) const;
	rgb_t& operator()(const int i, const int j);
	inline const rgb_t* data() const { return _pixels.data();}
	inline void resize(const int n) { _pixels.resize(n); }
	inline size_t size() const { return _pixels.size(); }
};

class render
{
	static inline int depth_reflection = 4;
public:
	static void gradient(Scene& sc);
	static rgbf_t geometry(const Ray& ray, Scene& sc, const Vec2i& pix = Vec2i(0, 0), int trace_lvl = 0);		  //�������������� �����������
	static rgbf_t diffusion(const Ray& ray, Scene& sc, const Vec2i& pix = Vec2i(0, 0), int trace_lvl = 0);		  //������������ �����������
	static rgbf_t phong_reflection(const Ray& ray, Scene& sc, const Vec2i& pix = Vec2i(0, 0), int trace_lvl = 0); //������ ��������� �����
	static rgbf_t shadow_model(const Ray& ray, Scene& sc, const Vec2i& pix = Vec2i(0, 0), int trace_lvl = 0);	  //������ � ������
	static rgbf_t trace_reflection(const Ray& ray, Scene& sc, const Vec2i& pix = Vec2i(0, 0), int trace_lvl = 0);  // ������ ��������� � ����������������
	static rgbf_t snell_refraction(const Ray& ray, Scene& sc, const Vec2i& pix = Vec2i(0,0), int trace_lvl = 0); // ������ ����������� ������
	static void set_depth_reflection(const int n) { depth_reflection = n; }
private:
	static bool check_shadow(const Ray& ray, const intersect_t& p, Scene& sc, Light& src); //��������� ������� ���������
};

#endif //RENDER_H
