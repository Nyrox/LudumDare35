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
    int life = 100;
};

#endif // UNIT_H
