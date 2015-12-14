#ifndef MAP_H
#define MAP_H

#include <vector>

#include "Unit.h"
#include "Animation.h"

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

	float zoom = -1.f;
	float targetZoom = zoom;

	float groundTop = 500;

    std::vector<Animation> corpse;

    Game* game;

    sf::RectangleShape background;

    sf::FloatRect spawnRect;

    sf::Vector2f leftLineStart;
    sf::Vector2f rightLineStart;
    sf::Vector2f leftLineEnd;
    sf::Vector2f rightLineEnd;

};

#endif // MAP_H
