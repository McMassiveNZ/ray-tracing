#include "camera.h"

camera::camera(point3 look_from, point3 look_at, v3 up, float vfov, float aspect_ratio, float aperture, float focus_distance)
{
	auto theta = degrees_to_radians(vfov);
	auto h = tan(theta*0.5f);
	auto viewport_height = 2.f * h;
	auto viewport_width = aspect_ratio * viewport_height;

	w = unit(look_from - look_at);
	u = unit(cross(up, w));
	v = cross(w, u);

	origin = look_from;
	horizontal = focus_distance * viewport_width * u;
	vertical = focus_distance * viewport_height * v;
	lower_left_corner = origin - horizontal*.5f - vertical*.5f - focus_distance * w;

	lens_radius = aperture*.5f;
}

ray camera::get_ray(float s, float t) const
{
	v3 rd = lens_radius * random_in_unit_disk();
	v3 offset = u * rd.x() + v * rd.y();

	return ray(
		origin + offset,
		lower_left_corner + s*horizontal + t*vertical - origin - offset);
}