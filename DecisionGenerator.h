#pragma once
#include <SFML/Graphics.hpp>
#include "Debug.h"

#include <vector>
#include "Decisions.h"

class Game;

class DecisionGenerator {
public:
	DecisionGenerator(Game* game);

	Decision* getDecision(int dangerLevel, Decision* filter = nullptr);

	void updateDangerLevel(int level);

	std::vector<Decision*> eligable;
	std::vector<Decision> decisions;

	Game* game;
};
