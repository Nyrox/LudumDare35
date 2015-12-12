#include "Game.h"


Game::Game(const BasicConfig& config) : window(config.video_mode, config.window_title, config.window_style) {


}

void Game::run() {

	sf::Event event;
	deltaClock.restart();

	while (window.isOpen()) {
		
		accumulatedTime += deltaClock.getElapsedTime();
		deltaTime = deltaClock.restart().asSeconds();
		
		
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				goto mainLoopEnd;
			}



			activeState->handleEvent(event);
		}

		window.clear();


		if (accumulatedTime.asMicroseconds() >= 1.0f / C_TICKRATE) {
			activeState->update();
			accumulatedTime -= sf::microseconds(1.0f / C_TICKRATE);
		}

		activeState->render(window);



		window.display();

	}

	mainLoopEnd:

	debug.log("Info", "Shutting down");
}