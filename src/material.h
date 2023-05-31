#pragma once

#include "common.h"
#include "vec3.h"

struct hit_record;
struct ray;

struct material
{
	class MaterialConcept
	{
	public:
		virtual ~MaterialConcept() = default;
		virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const = 0;
		virtual std::unique_ptr<MaterialConcept> clone() const = 0;
	};

	template <typename T>
	class MaterialModel : public MaterialConcept
	{
		T object;

	public:
		MaterialModel(T&& value)
			: object{std::forward<T>(value)}
		{
		}

		bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override
		{
			return ::scatter(object, r_in, rec, attenuation, scattered);
		}

		std::unique_ptr<MaterialConcept> clone() const override final
		{
			return std::make_unique<MaterialModel>(*this);
		}
	};

	friend bool scatter(const material& h, const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)
	{
		return h.pimpl->scatter(r_in, rec, attenuation, scattered);
	}

	std::unique_ptr<MaterialConcept> pimpl;

public:
	template <typename T>
	material(T&& t)
		: pimpl{std::make_unique<MaterialModel<T>>(std::forward<T>(t))}
	{
	}

	material(const material& s)
		: pimpl{s.pimpl->clone()}
	{
	}

	material& operator=(material&& s) noexcept
	{
		pimpl = s.pimpl->clone();
		return *this;
	}

	material(material&& s) = default;
	material& operator=(const material& s) = delete;
};
