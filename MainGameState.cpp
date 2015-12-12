#include "MainGameState.h"

#include "Game.h"



MainGameState::MainGameState(Game* t_game) : State(t_game) {

}

void MainGameState::update() {


	game->debug.log("Info", std::to_string(game->deltaTime));

}

void MainGameState::render(sf::RenderTarget& target) {



}

void MainGameState::handleEvent(const sf::Event& event) {

}