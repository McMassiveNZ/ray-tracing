#include "sphere.h"
#include "ray.h"
#include "hittable.h"

sphere::sphere(point3 c, float r, material mat) 
: center(c)
, radius(r)
, mat(std::move(mat))
{
}

bool hit(const sphere& sphere, const ray& r, float t_min, float t_max, hit_record& rec)
{
	v3 oc = r.origin - sphere.center;
	const float a = r.direction.length_sqr();
	const float half_b = dot(oc, r.direction);
	const float c = oc.length_sqr() - sphere.radius*sphere.radius;

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
	rec.normal = (rec.p - sphere.center) / sphere.radius;
	rec.mat = &sphere.mat;
	
	const auto outward_normal = (p - sphere.center) / sphere.radius;
	rec.set_face_normal(r, outward_normal);

	return true;
}