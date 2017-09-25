#include "MainMenuState.hpp"
#include "ResourceManager.hpp"

MainMenuState::MainMenuState(Game& game)
	: GameState(game) {

	m_backgroundHandle = ResourceManager::getInstance().addTexture("motorovka.jpg");
}

void MainMenuState::handleEvent(SDL_Event e) {
	if (e.type == SDL_KEYDOWN) {
		switch (e.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			m_game.closeGame();
			break;
		}
	}
}

void MainMenuState::handleInput() {
}

void MainMenuState::update() {

}

void MainMenuState::render(SDL_Window& renderTarget) {
	SDL_Surface* s = SDL_GetWindowSurface(&renderTarget);
	SDL_BlitSurface(ResourceManager::getInstance().getTexture(m_backgroundHandle)->getTexture(), NULL, s, NULL);
	SDL_UpdateWindowSurface(&renderTarget);
}
