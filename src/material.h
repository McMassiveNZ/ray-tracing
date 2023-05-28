#pragma once

#include "common.h"
#include "vec3.h"
#include "hittable.h"

struct hit_record;
struct ray;

struct material
{
	virtual bool scatter( const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const = 0;
};
