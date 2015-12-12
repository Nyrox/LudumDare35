#include "Unit.h"
#include "Game.h"

#include "Player.h"


const float Unit::baseFireRate = 0.5f;



Unit::Unit(Game* game, Player* player) : player(player) {

	shape.setSize({ 32, 32 });
	shape.setTexture(&game->textures["Infantry"]);
}

Unit::~Unit()
{
}

void Unit::render(sf::RenderTarget& target)
{
	sf::RenderStates states;
	states.transform = getTransform();

	target.draw(shape, states);
}
