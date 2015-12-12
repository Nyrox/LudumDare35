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
        unit.moving = ((unit.advancement+rightUnits.front().advancement+unit.range) <= 1.f);

    for(Unit& unit : rightUnits)
        unit.moving = ((unit.advancement+leftUnits.front().advancement+unit.range) <= 1.f);

    for(auto it = leftUnits.begin(); it != leftUnits.end(); it++)
    {
        if(it->life <= 0)
            it = leftUnits.begin() + (std::distance(leftUnits.begin(), leftUnits.erase(it)) - 1);
    }

    for(auto it = rightUnits.begin(); it != rightUnits.end(); it++)
    {
        if(it->life <= 0)
            it = rightUnits.begin() + (std::distance(rightUnits.begin(), rightUnits.erase(it)) - 1);
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
