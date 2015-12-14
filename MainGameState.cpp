#include "MainGameState.h"

#include "Game.h"

#include <iostream>

MainGameState::MainGameState(Game* t_game) : State(t_game), map({500, 500}, 600, t_game), generator(game)
{

//	decisionShape1.setSize({ 512 - 96, 242.0f - 32 });
//	decisionShape2.setSize({ 512 - 96, 242.0f - 32 });

    sf::Vector2f windowSize = (sf::Vector2f)game->window.getSize();

    decisionShape1.setSize({(312.f/1024.f)*windowSize.x,(100.f/580.f)*windowSize.y});
    decisionShape2.setSize(decisionShape1.getSize());

    decisionShape1.setPosition({ 20, windowSize.y - decisionShape1.getSize().y - 20});
    decisionShape2.setPosition({ windowSize.x - decisionShape2.getSize().x - 20, windowSize.y - decisionShape1.getSize().y - 20});

    decisionText1.setCharacterSize(12);
    decisionText2.setCharacterSize(12);

    decisionText1.setPosition(decisionShape1.getPosition() + decisionShape1.getSize()/2.f);
    decisionText2.setPosition(decisionShape2.getPosition() + decisionShape2.getSize()/2.f);

    sf::Font* font = &game->fonts.acquire("font", thor::ResourceLoader<sf::Font>(thor::Resources::fromFile<sf::Font>("assets/font.ttf")));

    decisionText1.setFont(*font);
    decisionText2.setFont(*font);

    killCountLeft.setCharacterSize(24);
    killCountRight.setCharacterSize(killCountLeft.getCharacterSize());

    killCountLeft.setFont(*font);
    killCountRight.setFont(*font);

    killCountLeft.setPosition({20, 20});
    killCountRight.setPosition({20, windowSize.x - 20 - getSize(killCountRight).x});

    frame.setPosition(0, 0);
    frame.setSize((sf::Vector2f)game->window.getSize());
    frame.setTexture(&game->textures.acquire("frame", thor::Resources::fromFile<sf::Texture>("assets/frame.png")));

    game->textures.acquire("Infantry", thor::Resources::fromFile<sf::Texture>("assets/all-new.png"));
    game->textures.acquire("bullet", thor::Resources::fromFile<sf::Texture>("assets/bullet.png"));
//	game->textures.acquire("Infantry", thor::Resources::fromFile<sf::Texture>("assets/animation.png"));
//	game->textures.acquire("Die", thor::Resources::fromFile<sf::Texture>("assets/die.png"));

    left.side = Map::LEFT;
    right.side = Map::RIGHT;

    setDangerLevel(1);
//	dangerLevel = 20;
}


void MainGameState::updatePlayer(Player& player)
{
    player.accumulator += game->deltaTime;
    while (player.accumulator >= 1.f / (Player::baseSpawnRate * player.spawnRateModifier * player.balancingSpawnRateModifier))
    {
        player.accumulator -= 1.f / (Player::baseSpawnRate * player.spawnRateModifier * player.balancingSpawnRateModifier);
        map.spawnUnit(Unit(game, &player), player.side);
    }
}

void MainGameState::update()
{

    if (substate == RUNNING)
    {
        decisionTimer += game->deltaTime;

        if (decisionTimer >= decisionDelay)
        {
            d1 = generator.getDecision(dangerLevel);
            d2 = generator.getDecision(dangerLevel, &d1);

            decisionShape1.setTexture(d1.image);
            decisionShape2.setTexture(d2.image);

            decisionText1.setString(d1.message);
            decisionText2.setString(d2.message);

            setTextSize(decisionText1, decisionShape1.getSize(), {10,50});
            setTextSize(decisionText2, decisionShape2.getSize(), {10,50});

            substate = CHOOSING;
            decisionTimer = 0;
        }

    }

    else if (substate == CHOOSING)
    {


    }

    updatePlayer(left);
    updatePlayer(right);

    killCountLeft.setString(std::to_string(left.deadCount));
    killCountRight.setString(std::to_string(right.deadCount));
    killCountRight.setPosition({game->window.getSize().x - 20 - getSize(killCountRight).x, 20});

    game->debug.log("Info", std::to_string(game->deltaTime));
    map.update(game->deltaTime);

    bool leftSmaller = map.leftUnits.size() < map.rightUnits.size()/2;
    if(leftSmaller || map.rightUnits.size() < map.leftUnits.size()/2)
    {
        int smallerCount = (leftSmaller ? map.leftUnits.size() : map.rightUnits.size());
        int biggerCount = (leftSmaller ? map.rightUnits.size() : map.leftUnits.size());

        Player& smaller = (leftSmaller ? left : right);
        Player& bigger = (leftSmaller ? right : left);
//
//        smaller.spawnRateModifier += smallerCount/biggerCount;
//        if(smallerCount == 0)
//            smaller.spawnRateModifier += bigger.spawnRateModifier * 2;

        smaller.balancingSpawnRateModifier = 5.f;
        bigger.balancingSpawnRateModifier = 1;
    }

    int totalUnitCount = map.leftUnits.size() + map.rightUnits.size();
    if(totalUnitCount >= nextDangerLevelUnitCount)
        setDangerLevel(dangerLevel + 1);
}

void MainGameState::setDangerLevel(int danger)
{
    dangerLevel = std::max(danger, dangerLevel); //dangerLevel can never decrease
    nextDangerLevelUnitCount = pow(10, dangerLevel);

    map.targetZoom = 3 - dangerLevel;
}

void MainGameState::render(sf::RenderTarget& target)
{
    map.render(target);

    target.draw(frame);

    if (substate == CHOOSING)
    {
        target.draw(decisionShape1);
        target.draw(decisionShape2);
        target.draw(decisionText1);
        target.draw(decisionText2);
    }

    target.draw(killCountLeft);
    target.draw(killCountRight);
}

void MainGameState::handleEvent(const sf::Event& event)
{


    if (substate == CHOOSING)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A)
            {
                handleDecision(&d1);
            }
            else if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D)
            {
                handleDecision(&d2);
            }
        }
    }


}

void MainGameState::handleDecision(Decision* decision)
{
    substate = RUNNING;

    decision->callback(game, &left);
    decision->callback(game, &right);

//    dangerLevel++;
    generator.updateDangerLevel(dangerLevel);
}
