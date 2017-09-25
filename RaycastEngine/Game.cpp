#include "Game.hpp"

#include "ResourceManager.hpp"

Game::Game(const WindowInfo& wInfo, const ContextInfo& cInfo) : 
	m_windowInfo(wInfo), m_contextInfo(cInfo) {
	
	initSDL();
	initGL();

	pushState<MainMenuState>(*this);
}

Game::~Game() {
	std::cout << "Destroying window" << std::endl;
	SDL_DestroyWindow(m_window);
	m_window = nullptr;
	IMG_Quit();
	SDL_Quit();
}

void Game::initSDL() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cerr << "Error: Failed to initialize SDL" << std::endl;
		return;
	}
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, m_contextInfo.major_version);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, m_contextInfo.minor_version);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);


	m_window = SDL_CreateWindow(m_windowInfo.name.c_str(),
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		m_windowInfo.width, m_windowInfo.height,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	int karel;
	int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		std::cerr << "Error: Failed to initialize SDL_image" << std::endl;
		return;
	}
}

void Game::initGL() {
	m_glContext = SDL_GL_CreateContext(m_window);
	if (m_glContext == NULL) {
		std::cerr << "Error: Failed to setup GL context" << std::endl;
		return;
	}
	int size;
	SDL_GL_GetAttribute(SDL_GL_DEPTH_SIZE, &size);
	std::cout << "DEPTH BUFFER RESOLUTION IS: " << size << std::endl;

	//GLEW
	glewExperimental = GL_TRUE;

	GLenum glewError = glewInit();

	if (glewError != GLEW_OK) {
		std::cerr << "Error: Failed to init GLEW" << std::endl;
		return;
	}
	/*
	if (GLEW_ARB_debug_output) {
	glDebugMessageCallbackARB((GLDEBUGPROCARB)&defaultDebugMessage, nullptr);
	}
	*/
}

void Game::run() {
	while (!m_shouldClose && !m_states.empty()) {

		auto& state = getCurrentState();

		//Update
		state.handleInput();

		//Render
		refresh();
		state.render(*m_window);
		//SDL_GL_SwapWindow(m_window);

		//Handle event
		handleEvent();
		checkPop();
	}
	//SDL_Delay(2000);
}

void Game::closeGame() {
	m_shouldClose = true;
}

void Game::refresh() {
	glClearColor(m_windowColour.r, m_windowColour.g, m_windowColour.b, m_windowColour.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Game::popState() {
	m_shouldPop = true;
}

void Game::handleEvent() {
	SDL_Event e;
	SDL_PollEvent(&e);

	getCurrentState().handleEvent(e);

	switch (e.type) {
	case SDL_QUIT:
		m_shouldClose = true;
		break;

	default:
		break;
	}
}

void Game::checkPop() {
	if (m_shouldPop) {
		m_states.pop_back();
	}
}

GameState& Game::getCurrentState() {
	return *m_states.back();
}

template<typename T, typename ...Args>
void Game::pushState(Args&&... args) {
	m_states.push_back(std::make_unique<T>(std::forward<Args>(args)...));
}