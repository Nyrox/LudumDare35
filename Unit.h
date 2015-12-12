#ifndef UNIT_H
#define UNIT_H

#include <SFML/Graphics.hpp>

class Unit
{
    public:
        Unit();
        virtual ~Unit();

        void render(sf::RenderTarget& target, sf::Vector2f position);

    float advancement = 0;
    float speed = 0.1f;
    int maxLife = 100;
    int life = maxLife;
    int damage = life/3;
    float range = 0.5;

    bool moving = true;
};

#endif // UNIT_H
