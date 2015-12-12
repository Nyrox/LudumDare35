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
    {
        if(unit.moving)
            unit.advancement += unit.speed*dt;
        else
            rightUnits.front().life = std::max(0.f, rightUnits.front().life-unit.damage*dt);
    }

    for(Unit& unit : rightUnits)
    {
        if(unit.moving)
            unit.advancement += unit.speed*dt;
        else
            leftUnits.front().life = std::max(0.f, leftUnits.front().life-unit.damage*dt);
    }

    std::sort(leftUnits.begin(), leftUnits.end(), [](const Unit& first, const Unit& second){return first.advancement > second.advancement;});
    std::sort(rightUnits.begin(), rightUnits.end(), [](const Unit& first, const Unit& second){return first.advancement > second.advancement;});

    for(Unit& unit : leftUnits)
        unit.moving = (rightUnits.size() ? (unit.advancement+rightUnits.front().advancement+unit.range) <= 1.f : true);

    for(Unit& unit : rightUnits)
        unit.moving = (leftUnits.size() ? (unit.advancement+leftUnits.front().advancement+unit.range) <= 1.f : true);

    for(auto it = leftUnits.begin(); it != leftUnits.end(); it++)
    {
		if (it->life <= 0 || it->advancement >= 1)
			it = leftUnits.erase(it);

		if (it == leftUnits.end())
			break;
    }

    for(auto it = rightUnits.begin(); it != rightUnits.end(); it++)
    {
		if (it->life <= 0 || it->advancement >= 1)
			it = rightUnits.erase(it);

		if (it == rightUnits.end())
			break;
    }

    leftUnitSpawnTime += dt;
    rightUnitSpawnTime += dt;

    if(leftUnitSpawnTime >= leftUnitRate)
    {
        leftUnits.emplace_back();
        leftUnitSpawnTime -= leftUnitRate;
    }

    if(rightUnitSpawnTime >= rightUnitRate)
    {
        rightUnits.emplace_back();
        rightUnitSpawnTime -= rightUnitRate;
    }
}

void Map::render(sf::RenderTarget& target)
{
    for(Unit& unit : leftUnits)
        unit.render(target, start + (end-start)*unit.advancement);

    for(Unit& unit : rightUnits)
        unit.render(target, end - (end-start)*unit.advancement);
}
