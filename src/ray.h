#pragma once

#include "vec3.h"

struct ray
{
    ray() = default;
    ray(point3 o, v3 d);
    
    v3 at(float t) const;

    point3 origin;
    v3 direction;
};

ray::ray(point3 o, v3 d)
: origin(o)
, direction(d)
{}

v3 ray::at(float t) const
{
    return origin + t*direction;
}