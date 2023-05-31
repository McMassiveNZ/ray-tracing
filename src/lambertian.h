#pragma once

#include "vec3.h"

struct ray;
struct hit_record;

struct lambertian
{
	lambertian() = default;
	lambertian(color c);

	color albedo;
};

bool scatter(const lambertian& mat, const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered);