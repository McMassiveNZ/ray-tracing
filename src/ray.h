#pragma once

#include "vec3.h"

struct ray
{
    ray() = default;
    ray(v3 o, v3 d);
    
    v3 point_at_parameter(float t) const;

    v3 origin;
    v3 direction;
};

ray::ray(v3 o, v3 d)
: origin(o)
, direction(d)
{}

v3 ray::point_at_parameter(float t) const
{
    return origin + t*direction;
}