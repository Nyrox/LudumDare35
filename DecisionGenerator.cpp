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

    addDecision("Advance the front.", "This will not end well...", 0, 2, 2, "AdvanceTheFront", [](Game* game, Player* player) -> void
    {
        dynamic_cast<MainGameState*>(game->activeState.get())->map.spawnUnit(Unit(game, player), player->side);
    });

    addDecision("Hold the line!", "Watching the enemy advance is kinda frightening...", 0, 2, 4, "HoldTheLine", [](Game* game, Player* player)
    {

    });

    addDecision("Recruit more locals...", "This will cost us a lot of support...", 0, 2, 2, "HoldTheLine", [](Game* game, Player* player)
    {
        dynamic_cast<MainGameState*>(game->activeState.get())->map.spawnUnit(Unit(game, player), player->side);        dynamic_cast<MainGameState*>(game->activeState.get())->map.spawnUnit(Unit(game, player), player->side);
        dynamic_cast<MainGameState*>(game->activeState.get())->map.spawnUnit(Unit(game, player), player->side);        dynamic_cast<MainGameState*>(game->activeState.get())->map.spawnUnit(Unit(game, player), player->side);
        dynamic_cast<MainGameState*>(game->activeState.get())->map.spawnUnit(Unit(game, player), player->side);        dynamic_cast<MainGameState*>(game->activeState.get())->map.spawnUnit(Unit(game, player), player->side);
    });

    addDecision("Spy on the enemy!", "Most of our spies got killed in a few days...", 0, 2, 2, "HoldTheLine", [](Game* game, Player* player)
    {
        player->deadCount += 10;

    });

    addDecision("Request bomb strikes!", "Our planes are just getting shot down and hurting our own men!", 0, 2, 2, "HoldTheLine", [](Game* game, Player* player)
    {
        player->deadCount += 20;
    });

    addDecision("Advance the local infrastructure!", "The locals appreciate your efforts, but so does the enemy...", 0, 2, 2, "HoldTheLine", [](Game* game, Player* player)
    {
        player->spawnRateModifier *= 1.1;
    });

    addDecision("Invest in Medication", "This will be a great help to our people!", 0, 2, 2, "HoldTheLine", [](Game* game, Player* player)
    {
        player->fireRateModifier *= 1.1;
    });

    addDecision("Try to raise money...", "A small shortterm help, but our reputation did suffer a lot...", 0, 2, 2, "HoldTheLine", [](Game* game, Player* player)
    {
        player->spawnRateModifier *= 0.9f;
		player->damageModifier *= 1.05;
    });

    addDecision("End the war...", "If you say so commander...", 3, 4, 4, "EndTheWar", [](Game* game, Player* player)
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
