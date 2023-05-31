#include "ray.h"

ray::ray(point3 o, v3 d)
: origin(o)
, direction(d)
{}

v3 ray::at(float t) const
{
    return origin + t*direction;
}