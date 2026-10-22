#pragma once

#include "gameobject.hpp"

struct Character
{
	int life;
	int maxLife;
	int mana;
	int maxMana;
	int damage;
	int armor;
	GameObject gameObject;

	Character(int life, int mana, int damage, int armor, GameObject gameObject)
		: life(life),
		  maxLife(life),
		  mana(mana),
		  maxMana(mana),
		  damage(damage),
		  armor(armor),
		  gameObject(gameObject)
	{
	}

	virtual ~Character() = default;
};
