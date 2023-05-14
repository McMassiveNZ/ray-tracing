#include <fstream>
#include "common.h"
#include "ray.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"

auto ray_color(const ray& r, const hittable& world) -> color
{
	hit_record result = {};
	if (world.hit(r, 0, infinity, result))
	{
		return 0.5f * (result.normal + color{1.f});
	}

	auto unit_direction = unit(r.direction);
	auto t = 0.5f * (unit_direction.y() + 1.f);
	return (1.f - t) * color(1.f) + t * color(0.5f, 0.7f, 1.f);
}

auto main() -> int
{
	// Image
	const auto aspect_ratio = 16.f / 9.f;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width / aspect_ratio);

	// World
	hittable_list world;
	auto* sphere_a = new sphere(point3(0.f, 0.f, -1.f), 0.5f);
	auto* sphere_b = new sphere(point3(0.f, -100.5f, -1.f), 100.f);
	world.objects.push_back(sphere_a);
	world.objects.push_back(sphere_b);

	// Camera
	const auto viewport_height = 2.f;
	const auto viewport_width = aspect_ratio * viewport_height;
	const auto focal_length = 1.f;

	const auto origin = point3{0.f};
	const auto horizontal = v3{viewport_width, 0.f, 0.f};
	const auto vertical = v3{0.f, viewport_height, 0.f};
	const auto bottom_left = origin - horizontal/2 - vertical/2 - v3{0, 0, focal_length};

	std::ofstream out_stream("z:\\git\\ray-tracing\\out.ppm");

	out_stream << "P3\n" << image_width << " " << image_height << "\n255\n";

	for (int j = image_height - 1; j >= 0; --j)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < image_width; ++i)
		{
			const float u = static_cast<float>(i) / static_cast<float>(image_width - 1);
			const float v = static_cast<float>(j) / static_cast<float>(image_height - 1);

			ray r(origin, bottom_left + u*horizontal + v*vertical);
			v3 col = ray_color(r, world);

			write_color(out_stream, col);
		}
	}
}

