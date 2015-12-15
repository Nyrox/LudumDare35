#include "Game.h"

Game::Game(const BasicConfig& config) : window(config.video_mode, config.window_title, config.window_style) {

//    window.setSize(window.getSize() - sf::Vector2u(50, 50));
	window.setView(window.getDefaultView());

	activeState = std::make_shared<MainGameState>(this);

//	buff.loadFromFile("./assets/music.ogg");
	music.openFromFile("./assets/music.ogg");
	music.play();
	music.setLoop(true);

}

void Game::run() {

	sf::Event event;
	deltaClock.restart();

	while (window.isOpen()) {
		if (nextState != nullptr) {
			activeState = nextState;
			nextState = nullptr;
		}

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				goto mainLoopEnd;
			}
			else if (event.type == sf::Event::Resized) {
				window.setView(window.getDefaultView());
			}

			activeState->handleEvent(event);
		}

		window.clear();

		deltaTime += deltaClock.restart().asSeconds();

		if (deltaTime >= 1.0f / C_TICKRATE) {
			activeState->update();
			deltaTime = 0;
		}

		activeState->render(window);

		window.display();
	}

	mainLoopEnd:

	debug.log("Info", "Shutting down");
}
