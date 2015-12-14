#include "DecisionGenerator.h"


#include "Game.h"
#include <memory>
#include "EndGameState.h"

DecisionGenerator::DecisionGenerator(Game* game) : game(game)
{

    decisions.emplace_back(
        "Advance the front!", 0, 20, 2, &game->textures.acquire("AdvanceTheFront", thor::ResourceLoader<sf::Texture>(thor::Resources::fromFile<sf::Texture>("assets/AdvanceTheFront.png"))), [](Game* game, Player* player) -> void
    {
        dynamic_cast<MainGameState*>(game->activeState.get())->map.spawnUnit(Unit(game, player), player->side);

    }
    );

    decisions.emplace_back(
        "Stay defensive!", 0, 10, 2, &game->textures.acquire("HoldTheLine", thor::ResourceLoader<sf::Texture>(thor::Resources::fromFile<sf::Texture>("assets/HoldTheLine.png"))), [](Game* game, Player*)
    {

    }
    );



    decisions.emplace_back(
        "End the war...", 3, 30, 3, &game->textures.acquire("EndTheWar", thor::ResourceLoader<sf::Texture>(thor::Resources::fromFile<sf::Texture>("assets/EndTheWar.png"))), [](Game* game, Player* player)
    {
        auto sp = std::make_shared<sf::RenderTexture>();
        sp->create(game->window.getSize().x, game->window.getSize().y);
        game->activeState->render(*sp.get());
        sp->display();
        game->nextState = std::make_shared<EndGameState>(game, sp);
    }
    );


    updateDangerLevel(0);

}

#include "MathHelper.h"

Decision DecisionGenerator::getDecision(int dangerLevel, Decision* filter)
{
	float totalPropability = 0;

	for (auto& it : eligable) {
		if (filter != nullptr && *filter == it)
			continue;

		totalPropability += it.probability;
	}

	float result = math::rand(totalPropability);
	float currentProb = 0;

	for (auto &it : eligable) {
		currentProb += it.probability;
		if (result <= currentProb) {
			if (filter != nullptr) {
				if (*filter == it && it.message != "End the war...") // #Bodged
					continue;
			}

			return it;
		}
	}

	throw "Nyrox is an idiot exception";
}

void DecisionGenerator::updateDangerLevel(int level)
{

	// remove decisions from the array that are too advanced
	for (auto it = eligable.begin(); it != eligable.end(); it++) {
		if (it->maxDangerLevel < level) {
			it = eligable.erase(it);
		}
		if (it == eligable.end())
			break;
	}

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
