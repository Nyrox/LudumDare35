#include "MainGameState.h"

#include "Game.h"

#include <iostream>


MainGameState::MainGameState(Game* t_game) : State(t_game) {

}

void MainGameState::update() {


	if (substate == RUNNING) {
		decisionTimer += game->deltaTime;


		if (decisionTimer >= 2) {
			d1 = generator.getDecision(dangerLevel);
			d2 = generator.getDecision(dangerLevel, &d1);
		
			
			std::cout << d1.message << " VS " << d2.message << std::endl;
			substate = CHOOSING;
		}

	}


	else if (substate == CHOOSING) {



	}



	game->debug.log("Info", std::to_string(game->deltaTime));

}

void MainGameState::render(sf::RenderTarget& target) {



}

void MainGameState::handleEvent(const sf::Event& event) {

}