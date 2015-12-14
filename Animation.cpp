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
