#include "dielectric.h"
#include "hittable.h"

dielectric::dielectric(float index_of_refraction)
	: ir(index_of_refraction)
{
}

static float reflectance(float cosine, float ref_idx)
{
	// Use Schlick's approximation for reflectance.
	auto r0 = (1.f - ref_idx) / (1.f + ref_idx);
	r0 = r0 * r0;
	return r0 + (1.f - r0) * powf((1.f - cosine), 5.f);
}

bool scatter(const dielectric& mat, const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)
{
	attenuation = color(1.0f, 1.0f, 1.0f);
	auto refraction_ratio = rec.front_face ? (1.0f / mat.ir) : mat.ir;

	v3 unit_direction = unit(r_in.direction);
	float cos_theta = fminf(dot(-unit_direction, rec.normal), 1.0f);
	float sin_theta = sqrtf(1.0f - cos_theta * cos_theta);

	bool cannot_refract = refraction_ratio * sin_theta > 1.0f;
	v3 direction;

	if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_real<float>())
		direction = reflect(unit_direction, rec.normal);
	else
		direction = refract(unit_direction, rec.normal, refraction_ratio);

	scattered = ray(rec.p, direction);
	return true;
}