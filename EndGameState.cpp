#include "EndGameState.h"

#include "Game.h"

EndGameState::EndGameState(Game* t_game, std::shared_ptr<sf::RenderTexture> screenshot) : State(t_game), screenshot(screenshot) {

	screenshotShape.setTexture(&screenshot->getTexture());
	screenshotShape.setSize((sf::Vector2f)game->window.getSize());


	blendShape.setSize(screenshotShape.getSize());



}




void EndGameState::handleEvent(const sf::Event& event) {

}

void EndGameState::update() {
	passedTime += game->deltaTime;

	if (passedTime <= endCutsceneLength) {
		blendShape.setFillColor(sf::Color(210, 80, 45, 170 * math::clamp(passedTime, 0.0f, endCutsceneLength) / endCutsceneLength));
	}
	else {
		blendShape.setFillColor(sf::Color(0, 0, 0, 255));
	}
	

}

void EndGameState::render(sf::RenderTarget& target) {

	
	target.draw(screenshotShape);
	target.draw(blendShape);
}
