#pragma once

struct GameObject;

struct Component
{
	GameObject *gameObject = nullptr;

	virtual ~Component() = default;
};