#pragma once
#include <string>
#include <iostream>

#include <SDL_image.h>

class Texture {
public:
	Texture() {
		std::cout << "Vytvareni textury" << std::endl;
	};

	~Texture() {
		std::cout << "Freeing texture" << std::endl;
		SDL_FreeSurface(m_texture);
	}

	bool loadFromFile(const std::string& filename) {
		m_texture = IMG_Load(filename.c_str());
		if (m_texture == NULL) {
			std::cout << "Error loading texture" << std::endl;
			return false;
		}
		return true;
	}

	SDL_Surface* getTexture() {
		return m_texture;
	}

private:
	SDL_Surface* m_texture;
};