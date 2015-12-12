#pragma once

class Game;

#include <SFML/Graphics.hpp>

class State {
public:
	State(Game* t_game) : game(t_game) {};


	virtual void handleEvent(const sf::Event& event){ }
	virtual void render(sf::RenderTarget& target){ }
	virtual void update(){ }


	Game* game;

};
