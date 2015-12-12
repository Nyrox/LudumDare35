#include "Map.h"

Map::Map(sf::Vector2f position, float length)
{
    this->position = position;
    start = position - sf::Vector2f(length/2.f, 0);
    end = position + sf::Vector2f(length/2.f, 0);

    leftUnits.emplace_back();
    rightUnits.emplace_back();
}

Map::~Map()
{
}

void Map::update(float dt)
{
    for(Unit& unit : leftUnits)
        unit.advancement += unit.speed*dt;

    for(Unit& unit : rightUnits)
        unit.advancement += unit.speed*dt;
}

void Map::render(sf::RenderTarget& target)
{
    for(Unit& unit : leftUnits)
        unit.render(target, start + (end-start)*unit.advancement);

    for(Unit& unit : rightUnits)
        unit.render(target, end - (end-start)*unit.advancement);
}
