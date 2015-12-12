#ifndef MAP_H
#define MAP_H

#include <vector>

#include "Unit.h"

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


	sf::Vector2f position;
	sf::Vector2f start;
	sf::Vector2f end;
};

#endif // MAP_H
