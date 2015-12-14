#include "Animation.h"

#include "MathHelper.h"

Animation::Animation()
{
    //ctor
}

Animation::~Animation()
{
//    delete ((sf::Animation*)this);
//    ((sf::Animation*)this)->~Animation();
}

void Animation::update(float dt)
{
    accumulator += dt;
    if(accumulator >= 1.f/fps)
    {
        accumulator -= 1.f/fps;
        if(++currentFrame > endFrame)
            currentFrame = (loop ? startFrame : endFrame);

        setCurrentFrame(currentFrame);
    }
}

void Animation::setCurrentFrame(int frame)
{
    currentFrame = frame;

    setTextureRect({sf::Vector2i(currentFrame%frameGrid.x, currentFrame/frameGrid.x)*frameSize, frameSize});
}
//
//void Animation::setSize(const sf::Vector2f& size)
//{
//    shape.setSize(size);
//}
//
//sf::Vector2f Animation::getSize()
//{
//    return shape.getSize();
//}
//
//void Animation::setTexture(const sf::Texture* texture, bool resetRect)
//{
//shape.setTexture(texture, resetRect);
//}
//
//void Animation::setTextureRect(const sf::IntRect& rect)
//{
//shape.setTextureRect(rect);
//}
//
//void Animation::setFillColor(const sf::Color& color)
//{
//shape.setFillColor(color);
//}
//
//void Animation::setPosition(float x, float y)
//{
//shape.setPosition(x, y);
//}
//
//void Animation::setPosition(const sf::Vector2f& position)
//{
//shape.setPosition(position);
//}
//
//void Animation::setScale(float factorX, float factorY)
//{
//shape.setScale(factorX, factorY);
//}
//
//void Animation::setScale(const sf::Vector2f& factors)
//{
//shape.setScale(factors);
//}
//
//sf::Vector2f Animation::getPosition()
//{
//return shape.getPosition();
//}
//
//sf::Vector2f Animation::getScale()
//{
//return shape.getScale();
//}
//
//void Animation::move(float offsetX, float offsetY)
//{
//shape.move(offsetX, offsetY);
//}
//
//void Animation::move(const sf::Vector2f& offset)
//{
//    shape.move(offset);
//}
//
