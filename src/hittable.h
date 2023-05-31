#pragma once

#include <memory>

#include "ray.h"

struct material;

struct hit_record
{
	point3 p;
	v3 normal;
	const material* mat;
	float t;
	bool front_face;

	inline void set_face_normal(const ray& r, v3 outward_normal);
};
	
void hit_record::set_face_normal(const ray& r, v3 outward_normal)
{
	front_face = dot(r.direction, outward_normal) < 0;
	normal = front_face ? outward_normal : -outward_normal;
}

class hittable
{
	class HittableConcept
	{
	public:
		virtual ~HittableConcept() = default;
		virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
		virtual std::unique_ptr<HittableConcept> clone() const = 0;
	};

	template <typename T>
	class HittableModel : public HittableConcept
	{
		T object;

	public:
		HittableModel(T&& value)
			: object{std::forward<T>(value)}
		{
		}

		bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const override final
		{
			return ::hit(object, r, t_min, t_max, rec);
		}

		std::unique_ptr<HittableConcept> clone() const override final
		{
			return std::make_unique<HittableModel>(*this);
		}
	};

	friend bool hit(const hittable& h, const ray& r, float t_min, float t_max, hit_record& rec)
	{
		return h.pimpl->hit(r, t_min, t_max, rec);
	}

	std::unique_ptr<HittableConcept> pimpl;

public:
	template <typename T>
	hittable(T&& t)
		: pimpl{std::make_unique<HittableModel<T>>(std::forward<T>(t))}
	{
	}

	hittable(const hittable& s)
		: pimpl{s.pimpl->clone()}
	{
	}

	hittable& operator=(hittable&& s) noexcept
	{
		pimpl = s.pimpl->clone();
		return *this;
	}

	hittable(hittable&& s) = default;
	hittable& operator=(const hittable& s) = delete;
};
