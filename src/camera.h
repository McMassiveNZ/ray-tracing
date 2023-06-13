#pragma once

#include "common.h"
#include "ray.h"

class camera
{
public:
	camera(point3 look_from, point3 look_at, v3 up, float vfov, float aspect_ratio);
	inline ray get_ray(float u, float v) const;

private:
	point3 origin;
	point3 lower_left_corner;
	v3 horizontal;
	v3 vertical;
};

camera::camera(point3 look_from, point3 look_at, v3 up, float vfov, float aspect_ratio)
{
	const auto theta = degrees_to_radians(vfov);
	const auto h = tanf(theta / 2);
	const auto viewport_height = 2.f * h;
	const auto viewport_width = aspect_ratio * viewport_height;
	const auto focal_length = 1.f;

	origin = v3{0.f};
	horizontal = v3{viewport_width, 0.f, 0.f};
	vertical = v3{0.f, viewport_height, 0.f};
	lower_left_corner = origin - horizontal/2.f - vertical/2.f - v3{0.f, 0.f, focal_length};

	auto w = unit(look_from - look_at);
	auto u = unit(cross(up, w));
	auto v = cross(w, u);

	origin = look_from;
	horizontal = viewport_width * u;
	vertical = viewport_height * v;
	lower_left_corner = origin - horizontal / 2 - vertical / 2 - w;
}

ray camera::get_ray(float s, float t) const
{
	return ray{origin, lower_left_corner + s*horizontal + t*vertical - origin};
}