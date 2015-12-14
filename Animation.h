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

//    void setSize(const sf::Vector2f& size);
//    sf::Vector2f getSize();
//    void setTexture(const sf::Texture* texture, bool resetRect = false);
//    void setTextureRect(const sf::IntRect& rect);
//    void setFillColor(const sf::Color& color);
//    void setPosition(float x, float y);
//    void setPosition(const sf::Vector2f& position);
//    void setScale(float factorX, float factorY);
//    void setScale(const sf::Vector2f& factors);
//    void setRotation(float rot)
//    {
//        shape.setRotation(rot);
//    }
//    void setOrigin(const sf::Vector2f& factors)
//    {
//        shape.setOrigin(factors);
//    }
//    sf::Vector2f getPosition();
//    sf::Vector2f getScale();
//    void move(float offsetX, float offsetY);
//    void move(const sf::Vector2f& offset);
//
//    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default)
//    {
//        target.draw(shape, states);
//    }
//
//
//    sf::RectangleShape shape;
};

#endif // ANIMATION_H
