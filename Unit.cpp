#include "Unit.h"

Unit::Unit()
{
}

Unit::~Unit()
{
}

void Unit::render(sf::RenderTarget& target, sf::Vector2f position)
{
    sf::RectangleShape shape;
    shape.setPosition(position);
    shape.setSize({50, 50});
    target.draw(shape);
}
