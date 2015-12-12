#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>

class Decision {
public:
	Decision(std::string message, int min, int max, int prob, sf::Texture* tex) : message(message), minDangerLevel(min), maxDangerLevel(max), probability(prob), image(tex) {

	}
	Decision(){ }
	virtual ~Decision() = default;




	std::string message;

	int minDangerLevel; // Used to retrieve the time at which to spawn this
	int maxDangerLevel; // Used to retrieve the time at which to stop spawning

	int probability; // Used to do calculations

	sf::Texture* image; // Background image



	/// Cheapstake
	bool operator==(const Decision& rhs) {
		if (message == rhs.message)
			return true;


	}

};

