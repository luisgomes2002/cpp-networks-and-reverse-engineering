#pragma once

#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "core/component.hpp"
#include "core/vec3.hpp"

struct GameObject
{
	std::string tag = "object";
	Vec3 position;

	GameObject() = default;

	GameObject(std::string tag, Vec3 position)
		: tag(std::move(tag)), position(position) {}

	GameObject(const GameObject &) = delete;
	GameObject &operator=(const GameObject &) = delete;

	GameObject(GameObject &&other) noexcept
		: tag(std::move(other.tag)), position(other.position),
		  components(std::move(other.components))
	{
		updateComponentOwners();
	}

	GameObject &operator=(GameObject &&other) noexcept
	{
		if (this != &other)
		{
			tag = std::move(other.tag);
			position = other.position;
			components = std::move(other.components);
			updateComponentOwners();
		}
		return *this;
	}

	template <typename T, typename... Args>
	T &addComponent(Args &&...args)
	{
		static_assert(std::is_base_of_v<Component, T>,
			"T must inherit from Component");

		auto component = std::make_unique<T>(
			std::forward<Args>(args)...);
		component->gameObject = this;

		T &reference = *component;
		components.push_back(std::move(component));
		return reference;
	}

	template <typename T>
	T *getComponent()
	{
		static_assert(std::is_base_of_v<Component, T>,
			"T must inherit from Component");

		for (const auto &component : components)
		{
			if (auto *result = dynamic_cast<T *>(component.get()))
				return result;
		}
		return nullptr;
	}

	template <typename T>
	const T *getComponent() const
	{
		static_assert(std::is_base_of_v<Component, T>,
			"T must inherit from Component");

		for (const auto &component : components)
		{
			if (const auto *result = dynamic_cast<const T *>(component.get()))
				return result;
		}
		return nullptr;
	}

private:
	std::vector<std::unique_ptr<Component>> components;

	void updateComponentOwners()
	{
		for (auto &component : components)
			component->gameObject = this;
	}
};
