#include "lambertian.h"
#include "hittable.h"

lambertian::lambertian(color c)
	: albedo(c)
{
}

bool scatter(const lambertian& mat, const ray&, const hit_record& record, color& attenuation, ray& scattered)
{
	auto scatter_direction = record.normal + random_unit_vector();

	// Catch degenerate scatter direction
	if (scatter_direction.near_zero())
		scatter_direction = record.normal;

	scattered = ray(record.p, scatter_direction);
	attenuation = mat.albedo;
	return true;
}