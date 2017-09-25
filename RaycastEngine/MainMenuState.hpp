#pragma once
#include <random>

#include "GameState.hpp"
#include "Game.hpp"
#include "Random.hpp"

class MainMenuState :
	public GameState
{
public:
	MainMenuState(Game& game);

	virtual void handleEvent(SDL_Event e) override;
	virtual void handleInput() override;
	virtual void update() override;
	virtual void render(SDL_Window & renderTarget) override;

private:

	size_t m_backgroundHandle;
};