#include <fstream>

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
			float r = static_cast<float>(i) / static_cast<float>(nx);
			float g = static_cast<float>(j) / static_cast<float>(ny);
			float b = 0.2f;

			int ir = static_cast<int>(255.9f * r);
			int ig = static_cast<int>(255.9f * g);
			int ib = static_cast<int>(255.9f * b);

			out_stream << ir << " " << ig << " " << ib << "\n";
		}
	}
}

