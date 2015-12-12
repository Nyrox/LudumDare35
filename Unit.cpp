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

    sf::RectangleShape lifeBar;

    lifeBar.setFillColor(sf::Color::Green);
    lifeBar.setPosition(position - sf::Vector2f(0, 30));
    lifeBar.setSize({50.f*((float)life/maxLife),5.f});
    target.draw(lifeBar);

    lifeBar.setFillColor(sf::Color::Red);
    lifeBar.setSize({50.f*((float)life/maxLife)-50.f, 5.f});
    lifeBar.setPosition(position - sf::Vector2f(-50, 30));
    target.draw(lifeBar);
}
