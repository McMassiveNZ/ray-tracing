#pragma once

#include <vector>

#include "hittable.h"

class hittable_list final : public hittable
{
public:
	hittable_list() = default;
	hittable_list(hittable* object);

	bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const override;

	std::vector<hittable*> objects;
};

hittable_list::hittable_list(hittable* object)
	: objects{object}
{
}

bool hittable_list::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
	hit_record temp_rec = {};
	bool hit_anything = false;
	auto closest_so_far = t_max;

	for ( const auto* obj : objects )
	{
		if (obj->hit(r, t_min, closest_so_far, temp_rec) )
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}

	return hit_anything;
}
