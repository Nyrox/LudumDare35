#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

class Animation : public sf::RectangleShape
{
    public:
        Animation();
        virtual ~Animation();

        void update(float dt);
        void setCurrentFrame(int frame);

        int currentFrame;
        int startFrame;
        int endFrame;

        float fps;
        float accumulator = 0;

        sf::Vector2i frameSize;
        sf::Vector2i frameGrid;

        bool loop = true;
};

#endif // ANIMATION_H
