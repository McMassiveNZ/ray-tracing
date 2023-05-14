#include <fstream>
#include "common.h"
#include "ray.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

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
	const int samples_per_pixel = 100;

	// World
	hittable_list world;
	auto* sphere_a = new sphere(point3(0.f, 0.f, -1.f), 0.5f);
	auto* sphere_b = new sphere(point3(0.f, -100.5f, -1.f), 100.f);
	world.objects.push_back(sphere_a);
	world.objects.push_back(sphere_b);

	// Camera
	camera cam;

	std::ofstream out_stream("z:\\git\\ray-tracing\\out.ppm");

	out_stream << "P3\n" << image_width << " " << image_height << "\n255\n";

	for (int j = image_height - 1; j >= 0; --j)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < image_width; ++i)
		{
			color pixel_color = {};
			for (int s = 0; s < samples_per_pixel; ++s)
			{
				auto u = (static_cast<float>(i) + random_real<float>()) / static_cast<float>(image_width - 1);
				auto v = (static_cast<float>(j) + random_real<float>()) / static_cast<float>(image_height - 1);

				ray r = cam.get_ray(u, v);
				pixel_color += ray_color(r, world);
			}
			write_color(out_stream, pixel_color, samples_per_pixel);
		}
	}
}

