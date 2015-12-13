#include "Map.h"
#include "Game.h"

Map::Map(sf::Vector2f position, float length, Game* game) : game(game)
{

}

Map::~Map()
{
}

#include "MathHelper.h"
#include "Player.h"

void Map::spawnUnit(Unit unit, Sides side)
{
    Unit& ref = (side == LEFT ? leftUnits : rightUnits).back();
    ref.push_back(unit);

    // Map a random factor onto the lines
    float result = math::rand(1.0);

    sf::Vector2f start = side == LEFT ? left_line_start : right_line_start;
    sf::Vector2f end = side == LEFT ? left_line_end : right_line_end;

    sf::Vector2f diff = end - start;

    sf::Vector2f position = start + diff * result;

    ref.setPosition(position);
    if (side == RIGHT) ref.setScale(-1, 1);

    ref.scale(4 - result, 4 - result);

    std::sort(ref.begin(), ref.end(), [](Unit& left, Unit& right){return left.getPosition().y < right.getPosition().y;});
}

void Map::updateUnits(Sides side, float dt)
{
    std::vector<Unit>& units = (side == LEFT ? leftUnits : rightUnits);
    std::vector<Unit>& enemys = (side == RIGHT ? leftUnits : rightUnits);

    for (Unit &it : units)
    {
        it.shape.update(dt);
        it.accumulator += dt;
        if(it.accumulator * it.player->fireRateModifier >= 1 / Unit::baseFireRate)
        {
            if(enemys.empty())
                continue;

//            it.shape.fps = 4/Unit::baseFireRate*it.player->fireRateModifier;
            it.shape.fps = 8;
            it.shape.startFrame = 8;
            it.shape.endFrame = 11;
            it.shape.setCurrentFrame(it.shape.startFrame);
            it.shape.loop = false;

            it.accumulator = 0;

            size_t result = math::rand(enemys.size() - 1);

            enemys.at(result).life -= Unit::baseDamage * it.player->damageModifier;
            enemys.at(result).flaggedToDie = enemys.at(result).life <= 0;
        }
        else if(it.shape.loop == false && it.shape.currentFrame == it.shape.endFrame)
            it.resetAnimation();
    }
}

void Map::removeDeadUnits(Sides side)
{
    std::vector<Unit>& units = (side == LEFT ? leftUnits : rightUnits);

    for (auto it = units.begin(); it != units.end(); it++)
    {
        if (it->flaggedToDie == true)
        {
            it->shape.fps = 2.5f;
            it->shape.startFrame = 0;
            it->shape.endFrame = 4;
            it->shape.setCurrentFrame(it->shape.startFrame);
            it->shape.setPosition(it->getPosition());
            it->shape.setScale(it->getScale());
            corpse.push_back(it->shape);

            it = units.erase(it);
        }

        if(it == units.end())
            break;
    }
}


void Map::update(float dt)
{

    for (auto it = corpse.begin(); it != corpse.end(); it++)
    {
        it->update(dt);
        if(it->currentFrame == it->endFrame)
            it = corpse.erase(it) - 1;
    }

    updateUnits(LEFT, dt);
    updateUnits(RIGHT, dt);

    removeDeadUnits(LEFT);
    removeDeadUnits(RIGHT);
}

void Map::render(sf::RenderTarget& target)
{
    for (Unit& unit : leftUnits)
        unit.render(target);

    for (Unit& unit : rightUnits)
        unit.render(target);

    for (Animation& anim : corpse)
        target.draw(anim);
}
