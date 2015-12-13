#ifndef MAP_H
#define MAP_H

#include <vector>

#include "Unit.h"
#include "Animation.h"

const sf::Vector2f left_line_start(100.0f, 600.0f);
const sf::Vector2f left_line_end(250.0f, 100.0f);
const sf::Vector2f right_line_start(1180.0f, 600.0f);
const sf::Vector2f right_line_end(930.0f, 100.0f);

class Game;

class Map {
public:
	Map(sf::Vector2f position, float length, Game* game);
	virtual ~Map();

	void addShootLine(sf::Vector2f start, sf::Vector2f end);

	enum Sides { LEFT, RIGHT };
	void spawnUnit(Unit unit, Sides side);

	void updateUnits(Sides side, float dt);
	void removeDeadUnits(Sides side);

	void update(float dt);
	void render(sf::RenderTarget& target);

	std::vector<Unit> leftUnits;
	std::vector<Unit> rightUnits;

	float rightUnitRate = 5.f;
	float leftUnitRate = 5.f;

	float zoom = 2;

    std::vector<Animation> corpse;

    Game* game;

    sf::RectangleShape background;

};

#endif // MAP_H
