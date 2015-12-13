#include "Unit.h"
#include "Game.h"

#include "Player.h"

const float Unit::baseFireRate = 0.5f;

Unit::Unit(Game* game, Player* player) : player(player) {

	shape.setSize({ 32, 32 });
	shape.setTexture(&game->textures["Infantry"]);

	resetAnimation();
}

void Unit::resetAnimation()
{
    shape.fps = 3;
	shape.startFrame = 12;
	shape.endFrame = 13;
	shape.frameSize = {64, 64};
	shape.frameGrid = {4, 4};
	shape.setCurrentFrame(shape.startFrame);
	shape.loop = true;
}

Unit::~Unit()
{
}

void Unit::render(sf::RenderTarget& target)
{
	sf::RenderStates states;
	states.transform = getTransform();
	states.transform.translate(-shape.getPosition());

	target.draw(shape, states);
}
