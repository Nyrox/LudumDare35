#ifndef MAP_H
#define MAP_H

#include <vector>

#include "Unit.h"


const sf::Vector2f left_line_start(100.0f, 600.0f);
const sf::Vector2f left_line_end(150.0f, 100.0f);
const sf::Vector2f right_line_start(800.0f, 600.0f);
const sf::Vector2f right_line_end(750.0f, 100.0f);

class Map {
public:
	Map(sf::Vector2f position, float length);
	virtual ~Map();

	enum Sides { LEFT, RIGHT };
	void spawnUnit(Unit unit, Sides side);

	void update(float dt);
	void render(sf::RenderTarget& target);


	std::vector<Unit> leftUnits;
	std::vector<Unit> rightUnits;

	float rightUnitRate = 5.f;
	float leftUnitRate = 5.f;


	
};

#endif // MAP_H
