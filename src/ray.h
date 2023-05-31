#pragma once

#include "vec3.h"

struct ray
{
    ray() = default;
    ray(point3 o, v3 d);
	~ray() = default;

    ray(const ray&) = default;
    ray(ray&&) = default;
    ray& operator=(const ray&) = default;
    ray& operator=(ray&&) = default;
    
    v3 at(float t) const;

    point3 origin;
    v3 direction;
};
