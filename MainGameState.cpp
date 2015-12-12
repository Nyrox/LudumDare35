#include "MainGameState.h"

#include "Game.h"

#include <iostream>


MainGameState::MainGameState(Game* t_game) : State(t_game), map({500, 500}, 600, t_game), generator(game) {

	decisionShape1.setSize({ game->window.getSize().x / 2 - 268.0f / 2, 242.0f });
	decisionShape2.setSize({ game->window.getSize().x / 2 - 268.0f / 2, 242.0f });

	decisionShape1.setPosition({ 40, game->window.getSize().y / 2 - decisionShape1.getSize().y / 2 });
	decisionShape2.setPosition({ game->window.getSize().x - decisionShape2.getSize().x - 40, game->window.getSize().y / 2 - decisionShape2.getSize().y / 2 });

//	game->textures.acquire("Infantry", thor::Resources::fromFile<sf::Texture>("assets/Infantry.png"));
	game->textures.acquire("Infantry", thor::Resources::fromFile<sf::Texture>("assets/animation.png"));
	game->textures.acquire("Die", thor::Resources::fromFile<sf::Texture>("assets/die.png"));

	map.spawnUnit(Unit(game, &left), Map::LEFT);
	map.spawnUnit(Unit(game, &right), Map::RIGHT);


	dangerLevel = 20;
}

void MainGameState::update() {


	if (substate == RUNNING) {
		decisionTimer += game->deltaTime;



		left.accumulator += game->deltaTime;
		if (left.accumulator * left.spawnRateModifier >= 1 / Player::baseSpawnRate) {
			left.accumulator = 0;
			map.spawnUnit(Unit(game, &left), Map::LEFT);

		}

		right.accumulator += game->deltaTime;
		if (right.accumulator * right.spawnRateModifier >= 1 / Player::baseSpawnRate) {
			right.accumulator = 0;
			map.spawnUnit(Unit(game, &right), Map::RIGHT);
		}



		if (decisionTimer >= 4) {
			d1 = generator.getDecision(dangerLevel);
			d2 = generator.getDecision(dangerLevel, &d1);



			decisionShape1.setTexture(d1.image);
			decisionShape2.setTexture(d2.image);

			decisionText1.setString(d1.message);
			decisionText2.setString(d2.message);


			substate = CHOOSING;
			decisionTimer = 0;
		}




	}


	else if (substate == CHOOSING) {



	}

	game->debug.log("Info", std::to_string(game->deltaTime));
	map.update(game->deltaTime);
}

void MainGameState::render(sf::RenderTarget& target) {

	map.render(target);

	if (substate == CHOOSING) {
		target.draw(decisionShape1);
		target.draw(decisionShape2);
		target.draw(decisionText1);
		target.draw(decisionText2);
	}


}

void MainGameState::handleEvent(const sf::Event& event) {


	if (substate == CHOOSING) {
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A) {
				handleDecision(d1);
			}
			else if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) {
				handleDecision(d2);
			}
		}
	}


}


void MainGameState::handleDecision(const Decision& decision) {
	
	substate = RUNNING;

	decision.callback(game, &left);




	dangerLevel++;
	generator.updateDangerLevel(dangerLevel);




	
}
