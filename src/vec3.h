#pragma once

#include <cmath>
#include <cstdlib>
#include <iostream>

struct v3
{
	v3() = default;
	inline v3(float e0, float e2, float e3);
	inline v3(float f);

	inline float x() const;
	inline float y() const;
	inline float z() const;
	inline float r() const;
	inline float g() const;
	inline float b() const;

	inline const v3& operator+() const;
	inline v3 operator-() const;

	inline v3& operator+=(v3 v);
	inline v3& operator-=(v3 v);
	inline v3& operator*=(v3 v);
	inline v3& operator/=(v3 v);
	inline v3& operator*=(float f);
	inline v3& operator/=(float f);

	inline float operator[](int i) const;
	inline float& operator[](int i);

	inline float length() const;
	inline float length_sqr() const;

	inline bool near_zero() const;

	float e[3];
};

using point3 = v3;
using color = v3;

inline v3::v3(float e0, float e1, float e2)
{
	e[0] = e0;
	e[1] = e1;
	e[2] = e2;
}

inline v3::v3(float f)
	: e{f, f, f}
{
}

inline float v3::x() const
{
	return e[0];
}

inline float v3::y() const
{
	return e[1];
}

inline float v3::z() const
{
	return e[2];
}

inline float v3::r() const
{
	return e[0];
}

inline float v3::g() const
{
	return e[1];
}

inline float v3::b() const
{
	return e[2];
}

inline const v3& v3::operator+() const
{
	return *this;
}

inline v3 v3::operator-() const
{
	return {-e[0], -e[1], -e[2]};
}

inline v3& v3::operator+=(v3 v)
{
	e[0] += v[0];
	e[1] += v[1];
	e[2] += v[2];
	return *this;
}

inline v3& v3::operator-=(v3 v)
{
	e[0] -= v[0];
	e[1] -= v[1];
	e[2] -= v[2];
	return *this;
}

inline v3& v3::operator*=(v3 v)
{
	e[0] *= v[0];
	e[1] *= v[1];
	e[2] *= v[2];
	return *this;
}

inline v3& v3::operator/=(v3 v)
{
	e[0] /= v[0];
	e[1] /= v[1];
	e[2] /= v[2];
	return *this;
}

inline v3& v3::operator*=(float f)
{
	e[0] *= f;
	e[1] *= f;
	e[2] *= f;
	return *this;
}

inline v3& v3::operator/=(float f)
{
	e[0] /= f;
	e[1] /= f;
	e[2] /= f;
	return *this;
}

inline float v3::operator[](int i) const
{
	return e[i];
}

inline float& v3::operator[](int i)
{
	return e[i];
}

inline float v3::length() const
{
	return sqrt(length_sqr());
}

inline float v3::length_sqr() const
{
	return (e[0] * e[0]) + (e[1] * e[1]) + (e[2] * e[2]);
}

inline bool v3::near_zero() const
{
	const float abs = 1e-8f;
	return {
		(fabsf(e[0]) < abs) &&
		(fabsf(e[1]) < abs) &&
		(fabsf(e[2]) < abs)
	};
}

inline std::ostream& operator<<(std::ostream& out, v3 v)
{
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline v3 operator+(v3 a, v3 b)
{
	return
	{
		a[0] += b[0],
		a[1] += b[1],
		a[2] += b[2]
	};
}

inline v3 operator-(v3 a, v3 b)
{
	return 
	{
		a[0] - b[0], 
		a[1] - b[1], 
		a[2] - b[2]
	};
}

inline v3 operator*(v3 a, v3 b)
{
	return 
	{
		a[0] * b[0],
		a[1] * b[1],
		a[2] * b[2]
	};
}

inline v3 operator/(v3 a, v3 b)
{
	return
	{
		a[0] / b[0],
		a[1] / b[1],
		a[2] / b[2]
	};
}

inline v3 operator*(v3 v, float f)
{
	return
	{
		v[0] * f,
		v[1] * f,
		v[2] * f
	};
}

inline v3 operator*(float f, v3 v)
{
	return
	{
		v[0] * f,
		v[1] * f,
		v[2] * f
	};
}

inline v3 operator/(v3 v, float f)
{
	return 
	{
		v[0] / f,
		v[1] / f,
		v[2] / f
	};
}

v3 unit(v3 v)
{
	return v / v.length();
}

float dot(v3 a, v3 b)
{
	return (a.e[0]*b.e[0]) + (a.e[1]*b.e[1]) + (a.e[2]*b.e[2]);
}

v3 cross(v3 a, v3 b)
{
	return 
	{
		a.e[1] * b.e[2] - a.e[2] * b.e[1],
		-(a.e[0] * b.e[2] - a.e[2] * b.e[0]),
		a.e[0] * b.e[1] - a.e[1] * b.e[0],

	};
}

v3 random()
{
	return { random_real<float>(), random_real<float>(), random_real<float>() };
}

v3 random(float min, float max)
{
	return {random_real<float>(min, max), random_real<float>(min, max), random_real<float>(min, max)};
}

v3 random_in_unit_sphere()
{
	while (true)
	{
		auto p = random(-1.f, 1.f);
		if (p.length_sqr() > 1.f)
			continue;

		return p;
	}
}

v3 random_unit_vector()
{
	return unit(random_in_unit_sphere());
}

v3 random_in_hemisphere(v3 normal)
{
	v3 in_unit_sphere = random_in_unit_sphere();
	if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
		return in_unit_sphere;
	else
		return -in_unit_sphere;
}

v3 reflect( v3 v, v3 n)
{
	return v - 2.f*dot(v, n) * n;
}
