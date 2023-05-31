#include "hittable_list.h"

hittable_list::hittable_list(hittable&& object)
	: objects{std::move(object)}
{
}

bool hit(const hittable_list& hl, const ray& r, float t_min, float t_max, hit_record& rec)
{
	hit_record temp_rec = {};
	bool hit_anything = false;
	auto closest_so_far = t_max;

	for ( const hittable& obj : hl.objects )
	{
		if ( hit(obj, r, t_min, closest_so_far, temp_rec) )
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}

	return hit_anything;
}