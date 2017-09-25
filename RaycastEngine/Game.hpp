#pragma once
#define NO_SDL_GLEXT

#include <memory>
#include <string>
#include <iostream>
#include <vector>

#include <GL/glew.h>//before opengl
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <glm/glm.hpp>

#include "GameState.hpp"
#include "StatePlaying.hpp"
#include "MainMenuState.hpp"

struct SDLWindowDeleter {
	void operator()(SDL_Window *w) const { SDL_DestroyWindow(w); }
};

struct WindowInfo {
	std::string name;
	int width;
	int height;

	WindowInfo() {
		name = "Game name";
		width = 800;
		height = 600;
	}

	WindowInfo(std::string n, int w, int h) :
		name(n), height(h), width(w) {};
};

struct ContextInfo {
	int major_version;
	int minor_version;
	bool use_core;

	ContextInfo() {
		major_version = 3;
		minor_version = 3;
		use_core = true;
	}

	ContextInfo(int major, int minor, bool useCore) :
		major_version(major), minor_version(minor), use_core(useCore) {};
};


class Game
{
public:
	Game(const WindowInfo& wInfo, const ContextInfo& cInfo);
	~Game();
	void run();
	const SDL_Window& getWindow();
	void closeGame();

public:

private:
	void initSDL();
	void initGL();
	void refresh();
	void popState();
	template<typename T, typename ...Args>
	void pushState(Args&&... arg);


private:
	void handleEvent();
	void checkPop();
	GameState& getCurrentState();

private:
	SDL_Window* m_window;
	SDL_GLContext m_glContext;
	WindowInfo m_windowInfo;
	ContextInfo m_contextInfo;
	glm::vec4 m_windowColour = glm::vec4(0.2f, 0.3f, 0.3f, 1.0f);
	bool m_shouldClose = false;
	bool m_shouldPop = false;
	std::vector<std::unique_ptr<GameState>> m_states;
};

