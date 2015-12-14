#include "DecisionGenerator.h"


#include "Game.h"
#include <memory>
#include "EndGameState.h"

DecisionGenerator::DecisionGenerator(Game* game) : game(game)
{

#define addTexture(textureName) game->textures.acquire(textureName, thor::Resources::fromFile<sf::Texture>("assets/" + std::string(textureName) + ".png"));

    addTexture("AdvanceTheFront");
    addTexture("HoldTheLine");
    addTexture("EndTheWar");

#define addDecision(Text, Effect, min, max, prob, textureName, lambda) decisions.emplace_back(Text, Effect, min, max, prob, &game->textures[textureName], lambda);

    addDecision("Become More Aggressive", "The Military Council approve", 0, 2, 2, "AdvanceTheFront", [](Game* game, Player* player) -> void
    {
        dynamic_cast<MainGameState*>(game->activeState.get())->map.spawnUnit(Unit(game, player), player->side);
    });

    addDecision("Stay defensive", "It kind of scary to stay back while the enemy go forward", 0, 2, 4, "HoldTheLine", [](Game* game, Player* player)
    {

    });

    addDecision("Recruit More Units", "The Population do not really understand your choices", 0, 2, 2, "HoldTheLine", [](Game* game, Player* player)
    {
        dynamic_cast<MainGameState*>(game->activeState.get())->map.spawnUnit(Unit(game, player), player->side);        dynamic_cast<MainGameState*>(game->activeState.get())->map.spawnUnit(Unit(game, player), player->side);
        dynamic_cast<MainGameState*>(game->activeState.get())->map.spawnUnit(Unit(game, player), player->side);        dynamic_cast<MainGameState*>(game->activeState.get())->map.spawnUnit(Unit(game, player), player->side);
        dynamic_cast<MainGameState*>(game->activeState.get())->map.spawnUnit(Unit(game, player), player->side);        dynamic_cast<MainGameState*>(game->activeState.get())->map.spawnUnit(Unit(game, player), player->side);
    });

    addDecision("Send Spy", "Why would you spy? is there not enough dead already?", 0, 2, 2, "HoldTheLine", [](Game* game, Player* player)
    {
        player->deadCount += 10;

    });

    addDecision("Request Bomber", "It seem like the bombs exploded in one of our camp", 0, 2, 2, "HoldTheLine", [](Game* game, Player* player)
    {
        player->deadCount += 20;
    });

    addDecision("Build Hospital", "Your population appreciate", 0, 2, 2, "HoldTheLine", [](Game* game, Player* player)
    {
        player->spawnRateModifier *= 1.1;
    });

    addDecision("Invest in Medication", "The Military Council doesn't like you to put money on this", 0, 2, 2, "HoldTheLine", [](Game* game, Player* player)
    {
        player->fireRateModifier *= 1.1;
    });

    addDecision("Make a money campaign", "People accept to give money but stop enrolling", 0, 2, 2, "HoldTheLine", [](Game* game, Player* player)
    {
        player->spawnRateModifier *= 0.9f;
    });

    addDecision("End the war...", "Well that's sad", 3, 3, 3, "EndTheWar", [](Game* game, Player* player)
    {
        auto sp = std::make_shared<sf::RenderTexture>();
        sp->create(game->window.getSize().x, game->window.getSize().y);
        game->activeState->render(*sp.get());
        sp->display();
        game->nextState = std::make_shared<EndGameState>(game, sp);
    });


    updateDangerLevel(0);

}

#include "MathHelper.h"

Decision DecisionGenerator::getDecision(int dangerLevel, Decision* filter)
{
//    float totalPropability = 0;
//
//    for (auto& it : eligable)
//    {
//        if (filter != nullptr && *filter == it)
//            continue;
//
//        totalPropability += it.probability;
//    }

//    float result = math::rand(totalPropability );
    float result = math::rand(eligable.size() - 1);
//    float currentProb = 0;


    while(filter && eligable[result] == *filter && (*filter).message != "End the war...")
    {
        result++;
        if(result >= eligable.size())
            result = 0;
    }

    return eligable[result];

//    for (auto &it : eligable)
//    {
//        currentProb += it.probability;
//        if (result <= currentProb)
//        {
//            if (filter != nullptr)
//            {
//                if (*filter == it && it.message != "End the war...") // #Bodged
//                    continue;
//            }
//
//
//            return it;
//        }
//    }

    throw "Nyrox is an idiot exception";
}

void DecisionGenerator::updateDangerLevel(int level)
{

//    // remove decisions from the array that are too advanced
//    for (auto it = eligable.begin(); it != eligable.end(); it++)
//    {
//        if (it->maxDangerLevel < level)
//        {
//            it = eligable.erase(it);
//        }
//        if (it == eligable.end())
//            break;
//    }
//

    eligable.clear();

    // add decisions to the array that are now eligable
    for (auto it = decisions.begin(); it != decisions.end(); it++)
    {
        if (it->minDangerLevel <= level && it->maxDangerLevel >= level)
        {
            for(int x = 0 ; x < it->probability; x++)
                eligable.push_back(*it);
        }
    }
}
