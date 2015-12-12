#include "MainGameState.h"

#include "Game.h"

#include <iostream>


MainGameState::MainGameState(Game* t_game) : State(t_game) {




	decisionShape1.setSize({ game->window.getSize().x / 2 - 140.0f / 2, 296.0f });
	decisionShape2.setSize({ game->window.getSize().x / 2 - 140.0f / 2, 296.0f });

	decisionShape1.setPosition({ 40, game->window.getSize().y / 2 - decisionShape1.getSize().y / 2 });
	decisionShape2.setPosition({ game->window.getSize().x - decisionShape2.getSize().x - 40, game->window.getSize().y / 2 - decisionShape2.getSize().y / 2 });








}

void MainGameState::update() {


	if (substate == RUNNING) {
		decisionTimer += game->deltaTime;


		if (decisionTimer >= 2) {
			d1 = generator.getDecision(dangerLevel);
			d2 = generator.getDecision(dangerLevel, &d1);
		
			

			decisionShape1.setTexture(d1.image);
			decisionShape2.setTexture(d2.image);

			decisionText1.setString(d1.message);
			decisionText2.setString(d2.message);


			substate = CHOOSING;
		}

	}


	else if (substate == CHOOSING) {



	}



	game->debug.log("Info", std::to_string(game->deltaTime));

}

void MainGameState::render(sf::RenderTarget& target) {
	
	if (substate == CHOOSING) {
		target.draw(decisionShape1);
		target.draw(decisionShape2);
		target.draw(decisionText1);
		target.draw(decisionText2);
	}


}

void MainGameState::handleEvent(const sf::Event& event) {


	if (substate == CHOOSING) {
		if (event.type == sf::Event::MouseButtonPressed) {
			if (decisionShape1.getGlobalBounds().contains((sf::Vector2f) sf::Mouse::getPosition(game->window))) {
				handleDecision(d1);
			}
			else if (
				decisionShape2.getGlobalBounds().contains((sf::Vector2f) sf::Mouse::getPosition(game->window))) {
				handleDecision(d2);
			}
		}
	}


}


void MainGameState::handleDecision(const Decision& decision) {
	std::cout << decision.message;


}
