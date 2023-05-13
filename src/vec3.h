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
	inline v3 unit() const;

	float e[3];
};

inline v3::v3(float e0, float e1, float e2)
{
	e[0] = e0;
	e[1] = e1;
	e[2] = e2;
}

inline v3::v3(float f)
{
	e[0] = f;
	e[1] = f;
	e[2] = f;
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
	return {e[0], e[1], e[2]};
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
	return sqrt((e[0] * e[0]) + (e[1] * e[1]) + (e[2] * e[2]));
}

inline float v3::length_sqr() const
{
	return (e[0] * e[0]) + (e[1] * e[1]) + (e[2] * e[2]);
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