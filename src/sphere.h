#pragma once

#include "vec3.h"
#include "material.h"

struct ray;

class sphere
{
public:
	sphere() = default;
	sphere(point3 c, float r, material mat);

	point3 center;
	float radius;
	material mat;
};

bool hit(const sphere& sphere, const ray& r, float t_min, float t_max, hit_record& rec);