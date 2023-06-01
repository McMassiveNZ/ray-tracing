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
public:
	template <typename T>
	hittable(T t)
		: self{std::make_shared<Model<T>>(std::move(t))}
	{
	}

	friend bool hit(const hittable& h, const ray& r, float t_min, float t_max, hit_record& rec)
	{
		return h.self->hit_(r, t_min, t_max, rec);
	}

private:
	struct Concept
	{
		virtual ~Concept() = default;
		virtual bool hit_(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
	};

	template <typename T>
	struct Model final : public Concept
	{
		Model(T value)
			: m_data{std::move(value)}
		{
		}

		bool hit_(const ray& r, float t_min, float t_max, hit_record& rec) const override final
		{
			return hit(m_data, r, t_min, t_max, rec);
		}

		T m_data;
	};

	std::shared_ptr<const Concept> self;
};
