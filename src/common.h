#pragma once

#include <cmath>
#include <limits>
#include <memory>
#include <random>

constexpr float infinity = std::numeric_limits<float>::infinity();
constexpr float pi = 3.141592653589f;

template< typename Real >
constexpr inline Real degrees_to_radians(Real degrees)
{
	return degrees * static_cast<Real>(pi) / Real{180};
}

template<typename Real>
constexpr inline Real random_real() 
{
	static std::uniform_real_distribution<Real> distribution(0.f, 1.f);
	static std::mt19937 generator;
	return distribution(generator);
}

template< typename Real >
constexpr inline Real clamp(Real x, Real min, Real max)
{
	if (x < min)
		return min;

	if (x > max)
		return max;

	return x;
}