#pragma once

#include "material.h"

struct lambertian : public material
{
	lambertian(color c);
	virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override;

	color albedo;
};

lambertian::lambertian(color c)
	: albedo(c)
{
}

bool lambertian::scatter(const ray&, const hit_record& record, color& attenuation, ray& scattered) const
{
	auto scatter_direction = record.normal + random_unit_vector();

	// Catch degenerate scatter direction
	if (scatter_direction.near_zero())
		scatter_direction = record.normal;

	scattered = ray(record.p, scatter_direction);
	attenuation = albedo;
	return true;
}