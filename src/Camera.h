#ifndef CAMERA_H
#define CAMERA_H

#include "types.h"
#include "objects.h"

class Camera
{
public:
	point_t _pos;	// ������� ������ � ������������		
	float _death;   // ������� ���� (~ ���������� �� ������ �� ��������� ���������) 

	static constexpr inline float _step_radius = 1.0f;			 // ��� �������� ������
	static constexpr inline float _step_angle = (2 * M_PI / 16); // ��� �������� ������
	static constexpr inline point_t _center_view = { 0, 0, 0 };	//����� ������ ������

	Mat3f _basis;			// ����� ��������� ��������� ���������
	point_t _spherical_pos;	// ������� ������ � ����������� �����������

public:

	Camera() : _pos(0, 0, 0), _spherical_pos(0, 0, 0), _basis{0}, _death(400) {};
	Camera(const point_t& position);
	Camera(const point_t& position, float death);
	Camera(const Camera& cam);

	Ray get_ray(const point_t& pixel_p);
	void move(int d_r, int d_theta, int d_phi);
	int to_cl(void*& data) const;
};

#endif //CAMERA_H
