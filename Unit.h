#ifndef UNIT_H
#define UNIT_H

#include <SFML/Graphics.hpp>

#include "Animation.h"

class Game;
class Player;


class Unit : public sf::Transformable {
public:
	Unit(Game* game, Player* player);
	virtual ~Unit();

	void resetAnimation();

	Animation shape;

	void render(sf::RenderTarget& target);

	sf::Vector2f targetPos = {0, 0};
	float speed = 0.f;
	float targetSpeed = 100.f;

	Player* player; // Used to get global modifiers

	int life = baseLife;
	float accumulator = 0; // Stores the time since the last time the Unit fired

	const static int baseLife = 100;
	const static int baseDamage = 0;

	const static float baseFireRate; // 0.5f

	bool flaggedToDie = false;
};



#endif // UNIT_H
