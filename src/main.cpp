#include <fstream>
#include "ray.h"

auto color(const ray& r) -> v3
{
	auto unit_direction = unit(r.direction);
	const float t = 0.5f * (unit_direction.y() + 1.f);
	return (1.f - t) * v3(1.f) + t * v3(0.5f, 0.7f, 1.f);
}

auto main() -> int
{
	int nx = 200;
	int ny = 100;

	std::ofstream out_stream("z:\\git\\ray-tracing\\out.ppm");

	out_stream << "P3\n" << nx << " " << ny << "\n255\n";
	v3 lower_left_corner(-2.f, -1.f, -1.f);
	v3 horizontal(4.f, 0.f, 0.f);
	v3 vertical(0.f, 2.f, 0.f);
	v3 origin(0.f);

	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; ++i)
		{
			const float u = static_cast<float>(i);
			const float v = static_cast<float>(j);

			ray r(origin, lower_left_corner + u * horizontal + v * vertical);
			v3 col = color(r);

			int ir = static_cast<int>(255.9f * col[0]);
			int ig = static_cast<int>(255.9f * col[1]);
			int ib = static_cast<int>(255.9f * col[2]);

			out_stream << ir << " " << ig << " " << ib << "\n";
		}
	}
}

