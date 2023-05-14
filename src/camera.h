#pragma once

#include "common.h"
#include "ray.h"

class camera
{
public:
	camera();
	inline ray get_ray(float u, float v) const;

private:
	point3 origin;
	point3 lower_left_corner;
	v3 horizontal;
	v3 vertical;
};

camera::camera()
{
	const auto aspect_ratio = 16.f / 9.f;
	const auto viewport_height = 2.f;
	const auto viewport_width = aspect_ratio * viewport_height;
	const auto focal_length = 1.f;

	origin = v3{0.f};
	horizontal = v3{viewport_width, 0.f, 0.f};
	vertical = v3{0.f, viewport_height, 0.f};
	lower_left_corner = origin - horizontal/2.f - vertical/2.f - v3{0.f, 0.f, focal_length};
}

ray camera::get_ray(float u, float v) const
{
	return ray{origin, lower_left_corner + u*horizontal + v*vertical - origin};
}