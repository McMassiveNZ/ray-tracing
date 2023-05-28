#pragma once

#include "hittable.h"
#include "vec3.h"
#include "material.h"

class sphere final : public hittable
{
public:
	sphere() = default;
	sphere(point3 c, float r, material* mat);

	bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const override;

	point3 center;
	float radius;
	material* mat;
};

sphere::sphere(point3 c, float r, material* mat) 
: center(c)
, radius(r)
, mat(mat)
{
}

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
	v3 oc = r.origin - center;
	const float a = r.direction.length_sqr();
	const float half_b = dot(oc, r.direction);
	const float c = oc.length_sqr() - radius*radius;

	const float discriminant = (half_b * half_b) - (a * c);
	if( discriminant < 0 )
		return false;

	auto sqrtd = sqrt(discriminant);

	auto root = (-half_b - sqrtd) / a;
	if ( root < t_min || t_max < root )
	{
		root = (-half_b + sqrtd) / a;
		if (root < t_min || t_max < root)
			return false;
	}

	const auto p = r.at(root);

	rec.t = root;
	rec.p = p;
	rec.normal = (rec.p - center) / radius;
	rec.mat = mat;
	
	const auto outward_normal = (p - center) / radius;
	rec.set_face_normal(r, outward_normal);

	return true;
}