#pragma once

#include "material.h"
#include "ray.h"

struct metal : public material
{
public:
	metal(color a, float fuzz);

	virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override;

	color albedo;
	float fuzz;
};

metal::metal(color a, float f)
	: albedo(a)
	, fuzz(f)
{}

 bool metal::scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const
{
	v3 reflected = reflect(unit(r_in.direction), rec.normal);
	scattered = ray(rec.p, reflected + fuzz*random_in_unit_sphere());
	attenuation = albedo;
	return (dot(scattered.direction, rec.normal) > 0);
}