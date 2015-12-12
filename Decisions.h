#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>

class Decision {
public:
	Decision(std::string message, int min, int max, int pref, int prob, sf::Texture* tex) : message(message), minDangerLevel(min), maxDangerLevel(max), prefferedDangerLevel(pref), probability(prob), image(tex) {

	}
	virtual ~Decision() = default;




	std::string message;

	int minDangerLevel; // Used to retrieve the time at which to spawn this
	int prefferedDangerLevel; // Used to retrieve the time at which this ist he likeliest, to interpolate based on
	int maxDangerLevel; // Used to retrieve the time at which to stop spawning

	int probability; // Used to do calculations

	sf::Texture* image; // Background image


};


