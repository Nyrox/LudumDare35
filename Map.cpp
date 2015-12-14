#include "Map.h"
#include "Game.h"

#include "MathHelper.h"

Map::Map(sf::Vector2f position, float length, Game* game) : game(game)
{
    background.setSize((sf::Vector2f)game->window.getSize() - sf::Vector2f(0, 20));
    background.setPosition(0, 0);
    background.setTexture(&game->textures.acquire("background", thor::Resources::fromFile<sf::Texture>("assets/Background.png")));

    leftLineEnd.x = (game->window.getSize().x/2.f) - 100;
    rightLineEnd.x = (game->window.getSize().x/2.f) + 100;

    leftLineStart.x = leftLineEnd.x - 100;
    rightLineStart.x = rightLineEnd.x + 100;
}

Map::~Map()
{
}

#include "MathHelper.h"
#include "Player.h"

void Map::spawnUnit(Unit unit, Sides side)
{
    std::vector<Unit>& vec = (side == LEFT ? leftUnits : rightUnits);
    vec.push_back(unit);
    Unit& ref = vec.back();

    // Map a random factor onto the lines
    float result = math::rand(1.0);
    float result2 = math::rand(1.0);

    ref.targetSpeed = math::rand(ref.targetSpeed*0.5f, ref.targetSpeed*3.f);

    sf::Vector2f start = (side == LEFT ? leftLineStart : rightLineStart);
    sf::Vector2f end = (side == LEFT ? leftLineEnd : rightLineEnd);

    ref.targetPos = start + (end - start) * sf::Vector2f(result, result);

    if (side == RIGHT)
        ref.setScale(-1, 1);

    ref.setPosition({side == RIGHT ? game->window.getSize().x+ref.shape.getSize().x*4.f : -ref.shape.getSize().x*4.f, ref.targetPos.y});

    ref.move({(game->window.getSize().x/2.f - game->window.getSize().x/2.f/zoom) * (side == LEFT ? 1.f : -1.f), 0.f});

    ref.scale(3 + ref.targetPos.y/game->window.getSize().y, 3 + ref.targetPos.y/game->window.getSize().y);

    std::sort(vec.begin(), vec.end(), [](Unit& left, Unit& right)
    {
        return left.getPosition().y < right.getPosition().y;
    });

}

void Map::addShootLine(sf::Vector2f start, sf::Vector2f end)
{
    Animation anim;
    anim.setTexture(&game->textures["bullet"]);
    anim.setFillColor(sf::Color {255, 255, 255, 255 / 3 });
    anim.setSize({math::getDistance(start, end), 5.f});
    anim.setOrigin({0.f, anim.getSize().y});
    anim.setPosition(start);
    anim.setRotation(math::vectorToAngle(start - end)+ 90);
    anim.fps = 30;
    anim.frameSize = {100, 1};
    anim.frameGrid = {1, 10};
    anim.startFrame = 0;
    anim.endFrame = 9;
    anim.setCurrentFrame(0);
    anim.loop = false;
    corpse.push_back(anim);
}

void Map::updateUnits(Sides side, float dt)
{
    std::vector<Unit>& units = (side == LEFT ? leftUnits : rightUnits);
    std::vector<Unit>& enemys = (side == RIGHT ? leftUnits : rightUnits);

    for (Unit &it : units)
    {
        it.shape.update(dt);
        it.accumulator += dt;
        if(it.targetPos != sf::Vector2f())
        {
            it.speed = math::lerp(it.speed, it.targetSpeed, dt*0.1f);
            it.move(math::normalize(it.targetPos-it.getPosition())*it.speed*dt);
            if(abs(math::length(it.getPosition() - it.targetPos) < 1))
                it.setPosition(it.targetPos), (it.targetPos = sf::Vector2f());
        }

        if(it.accumulator * it.player->fireRateModifier >= 1 / Unit::baseFireRate)
        {
            if(enemys.empty())
                continue;

            it.shape.fps = 8;
            it.shape.startFrame = 8;
            it.shape.endFrame = 11;
            it.shape.setCurrentFrame(it.shape.startFrame);
            it.shape.loop = false;

            it.accumulator = 0;

            size_t result = math::rand(enemys.size() - 1);

            enemys.at(result).life -= Unit::baseDamage * it.player->damageModifier;
            enemys.at(result).flaggedToDie = enemys.at(result).life <= 0;

            addShootLine(it.getPosition(), enemys.at(result).getPosition());
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
            it->shape.fps = 7.f;
            it->shape.accumulator = 0;
            it->shape.startFrame = 0;
            it->shape.endFrame = 8;
            it->shape.setCurrentFrame(it->shape.startFrame);
            it->shape.setPosition(it->getPosition());
            it->shape.setScale(it->getScale());
            it->shape.loop = false;
            corpse.push_back(it->shape);

            it->player->deadCount++;

            it = units.erase(it);

            if(it == units.end())
                break;
        }
    }
}

void Map::update(float dt)
{
    for (auto it = corpse.begin(); it != corpse.end(); it++)
    {
        it->update(dt);
        if(it->currentFrame >= it->endFrame)
        {
            it = corpse.erase(it);

            if(it == corpse.end());
            break;
        }
    }

    updateUnits(LEFT, dt);
    updateUnits(RIGHT, dt);

    removeDeadUnits(LEFT);
    removeDeadUnits(RIGHT);

    zoom = math::lerp(zoom, targetZoom, 3.f*dt);

    leftLineStart.y = (game->window.getSize().y/2.f)-(game->window.getSize().y/zoom);
    rightLineStart.y = leftLineStart.y;

    leftLineEnd.y = game->window.getSize().y - leftLineStart.y;
    rightLineEnd.y = leftLineEnd.y;

}

void Map::render(sf::RenderTarget& target)
{
    sf::View resetView = target.getView();
    sf::View view = resetView;

    view.setSize(view.getSize() / zoom);
    target.setView(view);

    target.draw(background);

    for (Unit& unit : leftUnits)
        unit.render(target);

    for (Unit& unit : rightUnits)
        unit.render(target);

    for (Animation& anim : corpse)
        target.draw(anim);

    target.setView(resetView);
}
