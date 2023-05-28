#pragma once

#include "common.h"
#include "vec3.h"
#include <iostream>

void write_color(std::ostream& out, color pixel_color, int samples_per_pixel)
{
	const float scale = 1.f / static_cast<float>(samples_per_pixel);
	const float r = sqrt(pixel_color.r() * scale);
	const float g = sqrt(pixel_color.g() * scale);
	const float b = sqrt(pixel_color.b() * scale);

	out << static_cast<int>(256 * clamp(r, 0.f, 0.999f)) << ' '
		<< static_cast<int>(256 * clamp(g, 0.f, 0.999f)) << ' '
		<< static_cast<int>(256 * clamp(b, 0.f, 0.999f)) << '\n';
}