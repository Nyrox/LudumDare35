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

	Animation shape;

	void render(sf::RenderTarget& target);

	Player* player; // Used to get global modifiers

	int life;
	float accumulator = 0; // Stores the time since the last time the Unit fired


	const static int baseLife = 100;
	const static int baseDamage = 40;

	const static float baseFireRate; // 0.5f


	bool flaggedToDie = false;
};



#endif // UNIT_H
