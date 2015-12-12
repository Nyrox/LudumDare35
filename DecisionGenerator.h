#pragma once
#include <SFML/Graphics.hpp>
#include "Debug.h"

#include <vector>
#include "Decisions.h"


class DecisionGenerator {
public:
	DecisionGenerator();


	void getDecision(int dangerLevel);





	std::vector<Decision> decisions;




};
