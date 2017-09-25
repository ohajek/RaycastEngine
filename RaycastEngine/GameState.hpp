#pragma once
#include <SDL.h>

#include "NonCopyable.hpp"

//#include "Game.hpp"

class Game;

class GameState : public NonCopyable
{
public:
	GameState(Game& game) :
		m_game(game) {}

	virtual ~GameState() = default;

	virtual void handleEvent(SDL_Event e) = 0;
	virtual void handleInput() = 0;
	virtual void update() = 0;
	virtual void render(SDL_Window& renderTarget) = 0;

protected:
	Game& m_game;
};

