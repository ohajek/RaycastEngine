#pragma once
#include "GameState.hpp"

class StatePlaying : public GameState
{
public:
	StatePlaying(Game& game);

	void handleEvent(SDL_Event e) override;
	void handleInput() override;
	void update() override;
	void render(SDL_Window& renderTarget) override;
};

