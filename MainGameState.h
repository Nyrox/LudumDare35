#pragma once
#include "State.h"
#include "Debug.h"
#include "MathHelper.h"

#include "DecisionGenerator.h"
#include "Map.h"
#include "Player.h"


class MainGameState : public State {
public:
	MainGameState(Game* game);

	virtual void handleEvent(const sf::Event& event) override;
	virtual void render(sf::RenderTarget& target) override;
	virtual void update() override;

	virtual void updatePlayer(Player& player);

	void handleDecision(Decision* decision);

	float decisionTimer = 0;
	float decisionDelay = 10;

	enum SubState {
		RUNNING, CHOOSING
	} substate = RUNNING;

	DecisionGenerator generator;
	Decision* d1;
	Decision* d2;

	void setDangerLevel(int danger);

	int nextDangerLevelUnitCount = 0;
	int dangerLevel = 0;

	Map map;

	sf::RectangleShape frame;
	sf::RectangleShape background;

	sf::RectangleShape decisionShape1;
	sf::RectangleShape decisionShape2;

	sf::Text decisionText1;
	sf::Text decisionText2;

	sf::Text killCountLeft;
	sf::Text killCountRight;

	Player left;
	Player right;
private:


};

