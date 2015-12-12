#pragma once
#include "State.h"
#include "Debug.h"
#include "MathHelper.h"

#include "DecisionGenerator.h"

class MainGameState : public State {
public: 
	MainGameState(Game* game);

	virtual void handleEvent(const sf::Event& event) override;
	virtual void render(sf::RenderTarget& target) override;
	virtual void update() override;





	float decisionTimer = 0;


	enum SubState {
		RUNNING, CHOOSING
	} substate = RUNNING;

	DecisionGenerator generator;
	Decision d1, d2;

	int dangerLevel = 0;

	sf::RectangleShape decisionShape1;
	sf::RectangleShape decisionShape2;

	sf::Text decisionText1;
	sf::Text decisionText2;



private:





};

