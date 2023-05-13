#include <fstream>

#include "vec3.h"

auto main() -> int
{
	int nx = 800;
	int ny = 600;

	std::ofstream out_stream("z:\\git\\ray-tracing\\out.ppm");

	out_stream << "P3\n" << nx << " " << ny << "\n255\n";

	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; ++i)
		{
			v3 col(static_cast<float>(i) / static_cast<float>(nx), static_cast<float>(j) / static_cast<float>(ny), 0.2f);

			int ir = static_cast<int>(255.9f * col[0]);
			int ig = static_cast<int>(255.9f * col[1]);
			int ib = static_cast<int>(255.9f * col[2]);

			out_stream << ir << " " << ig << " " << ib << "\n";
		}
	}
}

