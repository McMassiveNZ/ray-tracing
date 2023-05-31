#include <fstream>
#include <memory>

#include "common.h"
#include "ray.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"

auto ray_color(const ray& r, const hittable& world, int depth) -> color
{
	if (depth <= 0)
		return color{0.f, 0.f, 0.f};

	hit_record result = {};
	if (hit(world, r, 0.001f, infinity, result))
	{
		ray scattered;
		color attenuation;
		if (result.mat && scatter(*result.mat, r, result, attenuation, scattered))
			return attenuation * ray_color(scattered, world, depth - 1);
		return color(0, 0, 0);
	}

	auto unit_direction = unit(r.direction);
	auto t = 0.5f * (unit_direction.y() + 1.f);
	return (1.f - t) * color(1.f) + t * color(0.5f, 0.7f, 1.f);
}

auto main() -> int
{
	// Image
	const auto aspect_ratio = 16.f / 9.f;
	const int image_width = 800;
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	const int samples_per_pixel = 100;
	const int max_depth = 50;


	// World
	hittable_list world;
	world.objects.emplace_back(sphere(point3(0.0f, -100.5f, -1.0f), 100.0f, lambertian({0.8f, 0.8f, 0.f})));
	world.objects.emplace_back(sphere(point3(0.0f, 0.0f, -1.0f), 0.5f, lambertian({0.1f, 0.2f, 0.5f})));
	world.objects.emplace_back(sphere(point3(-1.0f, 0.0f, -1.0f), 0.5f, dielectric(1.5f)));
	world.objects.emplace_back(sphere(point3(-1.0f, 0.0f, -1.0f), -0.4f, dielectric(1.5f)));
	world.objects.emplace_back(sphere(point3(1.0f, 0.0f, -1.0f), 0.5f, metal({0.8f, 0.6f, 0.2f}, 0.1f)));

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
				pixel_color += ray_color(r, world, max_depth);
			}
			write_color(out_stream, pixel_color, samples_per_pixel);
		}
	}
}

