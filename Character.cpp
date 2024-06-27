#include <iostream>

struct Character
{
	std::string name;
	int health;
	int damage;

	Character(const std::string& name = "character_name", int health = 3, int damage = 1)
		: name(name), health(health), damage(damage) {}
};

