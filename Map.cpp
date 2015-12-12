#include "Map.h"

Map::Map(sf::Vector2f position, float length) {

}

Map::~Map() {
}

#include "MathHelper.h"
#include "Player.h"

void Map::spawnUnit(Unit unit, Sides side) {
	(side == LEFT ? leftUnits : rightUnits).push_back(unit);
	Unit& ref = (side == LEFT ? leftUnits : rightUnits).back();

	// Map a random factor onto the lines
	float result = math::rand(1.0);

	sf::Vector2f start = side == LEFT ? left_line_start : right_line_start;
	sf::Vector2f end = side == LEFT ? left_line_end : right_line_end;

	sf::Vector2f diff = end - start;

	sf::Vector2f position = start + diff * result;

	ref.setPosition(position);
	if (side == RIGHT) ref.setScale(-1, 1);

	ref.scale(1.2 - result, 1.2 - result);

}


void Map::update(float dt) {


	for (auto &it : leftUnits) {
		it.accumulator += dt;
		if (it.accumulator * it.player->fireRateModifier >= 1 / Unit::baseFireRate) {
			it.accumulator = 0;

			size_t result = math::rand(rightUnits.size() - 1);

			if(result >= rightUnits.size())
                continue;

			rightUnits.at(result).life -= Unit::baseDamage * it.player->damageModifier;
			if (rightUnits.at(result).life <= 0) {
				rightUnits.at(result).flaggedToDie = true;

			}

		}
	}

	for (auto it = rightUnits.begin(); it != rightUnits.end(); it++) {
		it->accumulator += dt;
		if (it->accumulator * it->player->fireRateModifier >= 1 / Unit::baseFireRate) {
			it->accumulator = 0;

			int result = math::rand(leftUnits.size() - 1);

			if(result >= leftUnits.size())
                continue;

			leftUnits.at(result).life -= Unit::baseDamage * it->player->damageModifier;
			if (leftUnits.at(result).life <= 0) {
				leftUnits.at(result).flaggedToDie = true;
			}
		}

		if (it->flaggedToDie == true) {
			it = rightUnits.erase(it);
			if (it == rightUnits.end()) {
				break;
			}
		}

	}

	for (auto it = leftUnits.begin(); it != leftUnits.end(); it++) {
		if (it->flaggedToDie == true) {
			it = leftUnits.erase(it);
		}

		if (it == leftUnits.end()) {
			break;
		}
	}


}

void Map::render(sf::RenderTarget& target) {
	for (Unit& unit : leftUnits)
		unit.render(target);

	for (Unit& unit : rightUnits)
		unit.render(target);
}
