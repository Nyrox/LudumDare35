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
    (side == LEFT ? leftUnits : rightUnits).push_back(unit);
    Unit& ref = (side == LEFT ? leftUnits : rightUnits).back();

    // Map a random factor onto the lines
    float result = math::rand(1.0);

    sf::Vector2f start = side == LEFT ? left_line_start : right_line_start;
    sf::Vector2f end = side == LEFT ? left_line_end : right_line_end;

    sf::Vector2f diff = end - start;

    sf::Vector2f position = start + diff * result;

    ref.setPosition(position);
    if (side == RIGHT) ref.setScale(-1, 1);

    ref.scale(1.4 - result, 1.4 - result);

}

void Map::updateUnits(Sides side, float dt)
{
    std::vector<Unit>& units = (side == LEFT ? leftUnits : rightUnits);
    std::vector<Unit>& enemys = (side == RIGHT ? leftUnits : rightUnits);

    for (auto &it : units)
    {
        it.shape.update(dt);
        it.accumulator += dt;
        if (it.accumulator * it.player->fireRateModifier >= 1 / Unit::baseFireRate)
        {
            it.accumulator = 0;

            size_t result = math::rand(enemys.size() - 1);

            if(result >= enemys.size())
                continue;

            enemys.at(result).life -= Unit::baseDamage * it.player->damageModifier;
            enemys.at(result).flaggedToDie = enemys.at(result).life <= 0;
        }
    }
}

void Map::removeDeadUnits(Sides side)
{
    std::vector<Unit>& units = (side == LEFT ? leftUnits : rightUnits);

    for (auto it = units.begin(); it != units.end(); it++)
    {
        if (it->flaggedToDie == true)
        {
            Animation anim;
            anim.setTexture(&game->textures["Die"]);
            anim.fps = 2;
            anim.startFrame = 0;
            anim.endFrame = 4;
            anim.frameSize = {64, 64};
            anim.frameGrid = {4, 4};
            anim.setCurrentFrame(0);
//            anim.setPosition(it->getPosition());
//            anim.setScale(it->getScale());
            anim.setPosition({500, 500});
            corpse.push_back(anim);

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
//        it->update(dt);
//        if(it->currentFrame == it->endFrame)
//            it = corpse.erase(it) - 1;
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
