#pragma once

#include <SFML\Audio.hpp>

#include "State.h"
#include "MainGameState.h"

#include <memory>

#include "Debug.h"
#include "BasicConfig.h"
#include "DecisionGenerator.h"

constexpr float C_TICKRATE = 60;

class Game {
public:

	Game(const BasicConfig& config);


	void run();
	



	std::shared_ptr<State> activeState = std::make_shared<MainGameState>(this);

	
	thor::ResourceHolder<sf::Texture, std::string> textures;
	


	sf::RenderWindow window;
	
	Debug debug;


	sf::Clock deltaClock;
	float deltaTime = 0;
	sf::Time accumulatedTime = sf::Time::Zero;

private:
	


};




