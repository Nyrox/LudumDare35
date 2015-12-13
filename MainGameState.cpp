#include "MainGameState.h"

#include "Game.h"

#include <iostream>

MainGameState::MainGameState(Game* t_game) : State(t_game), map({500, 500}, 600, t_game), generator(game) {

	decisionShape1.setSize({ 512 - 96, 242.0f - 32 });
	decisionShape2.setSize({ 512 - 96, 242.0f - 32 });

	decisionShape1.setPosition({ 80, game->window.getSize().y / 2 - decisionShape1.getSize().y / 2 });
	decisionShape2.setPosition({ game->window.getSize().x - decisionShape2.getSize().x - 80, game->window.getSize().y / 2 - decisionShape2.getSize().y / 2 });

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

	game->textures.acquire("Infantry", thor::Resources::fromFile<sf::Texture>("assets/all-new.png"));
	game->textures.acquire("bullet", thor::Resources::fromFile<sf::Texture>("assets/bullet.png"));
//	game->textures.acquire("Infantry", thor::Resources::fromFile<sf::Texture>("assets/animation.png"));
//	game->textures.acquire("Die", thor::Resources::fromFile<sf::Texture>("assets/die.png"));

	map.spawnUnit(Unit(game, &left), Map::LEFT);
	map.spawnUnit(Unit(game, &right), Map::RIGHT);


//	dangerLevel = 20;
}

void MainGameState::update() {

	if (substate == RUNNING) {
		decisionTimer += game->deltaTime;

		left.accumulator += game->deltaTime;
		while (left.accumulator * left.spawnRateModifier >= 1 / Player::baseSpawnRate) {
			left.accumulator -= 1 / Player::baseSpawnRate;
			map.spawnUnit(Unit(game, &left), Map::LEFT);
		}

		right.accumulator += game->deltaTime;
		while (right.accumulator * right.spawnRateModifier >= 1 / Player::baseSpawnRate) {
			right.accumulator -= 1 / Player::baseSpawnRate;
			map.spawnUnit(Unit(game, &right), Map::RIGHT);
		}

		if (decisionTimer >= decisionDelay) {
			d1 = generator.getDecision(dangerLevel);
			d2 = generator.getDecision(dangerLevel, d1);

			decisionShape1.setTexture(d1->image);
			decisionShape2.setTexture(d2->image);

			decisionText1.setString(d1->message);
			decisionText2.setString(d2->message);

			setTextSize(decisionText1, decisionShape1.getSize(), {10,50});
			setTextSize(decisionText2, decisionShape2.getSize(), {10,50});

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

void MainGameState::handleDecision(Decision* decision) {

	substate = RUNNING;

	decision->callback(game, &left);

	dangerLevel++;
	generator.updateDangerLevel(dangerLevel);
}
