#include "DecisionGenerator.h"



DecisionGenerator::DecisionGenerator() {

	decisions.emplace_back(
			"Advance the front!", 0, 20, 2, nullptr
		);

	decisions.emplace_back(
			"Stay defensive!", 0, 10, 2, nullptr
		);

	updateDangerLevel(0);

}

#include "MathHelper.h"

Decision DecisionGenerator::getDecision(int dangerLevel, Decision* filter) {

	float totalPropability = 0;

	for (auto& it : eligable) {
		totalPropability += it.probability;
	}

	float result = math::rand(totalPropability);
	float currentProb = 0;

	for (auto &it : eligable) {
		currentProb += it.probability;
		if (result <= currentProb) {
			if (filter != nullptr) {
				if (*filter == it)
					continue;
			} else
				return it;

		}
	}

	throw "Nyrox is an idiot exception";
}

void DecisionGenerator::updateDangerLevel(int level) {

	// remove decisions from the array that are too advanced
	for (auto it = eligable.begin(); it != eligable.end(); it++) {
		if (it->maxDangerLevel > level) {
			it = eligable.erase(it);
		}

		if (it == eligable.end()) {
			break;
		}
	}


	// add decisions to the array that are now eligable
	for (auto it = decisions.begin(); it != decisions.end(); it++) {
		if (it->minDangerLevel == level) {
			eligable.push_back(*it);
			it = decisions.erase(it);
			it--;
		}
	}
}
