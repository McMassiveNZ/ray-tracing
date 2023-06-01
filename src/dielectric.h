#pragma once

#include "vec3.h"

struct ray;
struct hit_record;

struct dielectric
{
	dielectric(float index_of_refraction);

	float ir;
};

bool scatter(const dielectric& material, const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered);