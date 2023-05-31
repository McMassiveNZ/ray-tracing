#pragma once

#include "vec3.h"

struct ray;
struct hit_record;

struct metal
{
public:
	metal() = default;
	metal(color a, float fuzz);

	color albedo;
	float fuzz;
};

 bool scatter(const metal& mat, const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered);