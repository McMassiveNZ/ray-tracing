#pragma once

#include "common.h"
#include "vec3.h"

struct hit_record;
struct ray;

struct material
{
	template <typename T>
	material(T t)
		: self{std::make_shared<Model<T>>(std::move(t))}
	{
	}

	friend bool scatter(const material& h, const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)
	{
		return h.self->scatter_(r_in, rec, attenuation, scattered);
	}

private:
	struct Concept
	{
		virtual ~Concept() = default;
		virtual bool scatter_(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const = 0;
	};

	template <typename T>
	struct Model final : public Concept
	{
		Model(T&& value)
			: m_data{std::move(value)}
		{
		}

		bool scatter_(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override
		{
			return scatter(m_data, r_in, rec, attenuation, scattered);
		}

		T m_data;
	};

	std::shared_ptr<const Concept> self;
};
