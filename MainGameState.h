#pragma once
#include "State.h"
#include "Debug.h"
#include "MathHelper.h"


class MainGameState : public State {
public: 
	MainGameState(Game* game);

	virtual void handleEvent(const sf::Event& event) override;
	virtual void render(sf::RenderTarget& target) override;
	virtual void update() override;






private:



};

