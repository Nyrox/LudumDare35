#include "EndGameState.h"

#include "Game.h"

EndGameState::EndGameState(Game* t_game, std::shared_ptr<sf::RenderTexture> screenshot) : State(t_game), screenshot(screenshot) {

	screenshotShape.setTexture(&screenshot->getTexture());
	screenshotShape.setSize((sf::Vector2f)game->window.getSize());


	blendShape.setSize(screenshotShape.getSize());

	    sf::Font* font = &game->fonts["font"];
	    gameOverShape.setFont(*font);
	    gameOverShape.setCharacterSize(36);
	    gameOverShape.setPosition((sf::Vector2f)game->window.getSize()/2.f);
	    gameOverShape.setString("War is never the end");


//	gameOverShape.Colo(sf::Color(255, 255, 255, 255));
//	gameOverShape.setTexture(&game->textures.acquire("GameOver", thor::ResourceLoader<sf::Texture>(thor::Resources::fromFile<sf::Texture>("assets/GameOver.png"))));
//	gameOverShape.setSize((sf::Vector2f)game->window.getSize());


}




void EndGameState::handleEvent(const sf::Event& event) {

}

void EndGameState::update() {
	passedTime += game->deltaTime;

	if (passedTime <= endCutsceneLength) {
		blendShape.setFillColor(sf::Color(210, 80, 45, 170 * math::clamp(passedTime, 0.0f, endCutsceneLength) / endCutsceneLength));
	}
	else {
		passedTime2 += game->deltaTime;

		blendShape.setFillColor(sf::Color(0, 0, 0, 255));
//		gameOverShape.setFillColor(sf::Color(255, 255, 255, 255 * math::clamp(passedTime2, 0.0f, gameOverFadeInTime) / gameOverFadeInTime));
	}


}

void EndGameState::render(sf::RenderTarget& target) {


	target.draw(screenshotShape);
	target.draw(blendShape);
	target.draw(gameOverShape);
}
