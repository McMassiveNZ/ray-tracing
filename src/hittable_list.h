#pragma once

#include <vector>
#include "hittable.h"

struct ray;

class hittable_list
{
public:
	hittable_list() = default;
	hittable_list(hittable&& object);

	std::vector<hittable> objects;
};

bool hit(const hittable_list& hl, const ray& r, float t_min, float t_max, hit_record& rec);