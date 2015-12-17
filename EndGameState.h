#pragma once
#include "State.h"

#include <memory>
#include <SFML/Graphics.hpp>


constexpr float endCutsceneLength = 10;
constexpr float gameOverFadeInTime = 5;

class EndGameState : public State {
public:
	EndGameState(Game* t_game, std::shared_ptr<sf::RenderTexture> screenshot);

	virtual void handleEvent(const sf::Event& event) override;
	virtual void update() override;
	virtual void render(sf::RenderTarget& target) override;



	std::shared_ptr<sf::RenderTexture> screenshot;
	sf::RectangleShape screenshotShape;
	sf::RectangleShape blendShape;

	sf::RectangleShape gameOverShape;


	float passedTime = 0;
	float passedTime2 = 0;

};
