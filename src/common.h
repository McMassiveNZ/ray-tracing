#pragma once

#include <cmath>
#include <limits>
#include <memory>

constexpr float infinity = std::numeric_limits<float>::infinity();
constexpr float pi = 3.141592653589f;

template< typename Real >
constexpr inline Real degrees_to_radians(Real degrees)
{
	return degrees * static_cast<Real>(pi) / Real{180};
}