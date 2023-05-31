#include "metal.h"
#include "hittable.h"

metal::metal(color a, float f)
	: albedo(a)
	, fuzz(f)
{}

bool scatter(const metal& mat, const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)
{
	v3 reflected = reflect(unit(r_in.direction), rec.normal);
	scattered = ray(rec.p, reflected + mat.fuzz*random_in_unit_sphere());
	attenuation = mat.albedo;
	return (dot(scattered.direction, rec.normal) > 0);
}