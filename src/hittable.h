#pragma once

#include "ray.h"
#include "material.h"

struct hit_record
{
	point3 p;
	v3 normal;
	material* mat;
	float t;
	bool front_face;

	inline void set_face_normal(const ray& r, v3 outward_normal);
};
	
void hit_record::set_face_normal(const ray& r, v3 outward_normal)
{
	front_face = dot(r.direction, outward_normal) < 0;
	normal = front_face ? outward_normal : -outward_normal;
}

class hittable
{
public:
	virtual ~hittable() = default;
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};