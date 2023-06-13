#pragma once

#include "common.h"
#include "ray.h"

class camera
{
public:
	camera(point3 look_from, point3 look_at, v3 up, float vfov, float aspect_ratio, float aperture, float focus_distance);
	ray get_ray(float u, float v) const;

private:
	point3 origin;
	point3 lower_left_corner;
	v3 horizontal;
	v3 vertical;
	v3 u;
	v3 v;
	v3 w;
	float lens_radius;
};
