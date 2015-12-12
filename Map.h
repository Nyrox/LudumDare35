#ifndef MAP_H
#define MAP_H

#include <vector>

#include "Unit.h"

class Map
{
    public:
        Map(sf::Vector2f position, float length);
        virtual ~Map();

        void update(float dt);
        void render(sf::RenderTarget& target);

    std::vector<Unit> leftUnits;
    std::vector<Unit> rightUnits;

    sf::Vector2f position;
    sf::Vector2f start;
    sf::Vector2f end;
};

#endif // MAP_H
