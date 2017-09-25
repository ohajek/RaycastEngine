#pragma once

#include <unordered_map>
#include <string>

#include "NonCopyable.hpp"
#include "NonMoveable.hpp"
#include "Resource.hpp"

class ResourceManager :
	public NonCopyable,
	public NonMoveable
{
public:
	~ResourceManager() {
		std::cout << "Destroying manager" << std::endl;
	}

	static ResourceManager& getInstance() {
		static ResourceManager manager;
		return manager;
	}

	size_t addTexture(const std::string& filename) {
		Resource<Texture> tmp;
		if (!tmp.loadFromFile(filename)) {
			tmp.loadFromFile(m_failTexture);
			m_textures.insert(std::make_pair(m_textures.size(), tmp));
		}
		else {
			m_textures.insert(std::make_pair(m_textures.size(), tmp));
		}
		return m_textures.size() - 1;
	}

	Resource<Texture>& getTexture(size_t handle) {
		if (m_textures.find(handle) != m_textures.end()) {
			return m_textures.at(handle);
		}
		else {
			std::cerr << "No texture found!" << std::endl;
			return m_textures.at(0);
		}
	}

private:
	ResourceManager() {
		Resource<Texture> tmp;
		tmp.loadFromFile(m_failTexture);
		m_textures.insert(std::make_pair(m_textures.size(), tmp));
	};


private:
	std::unordered_map<size_t, Resource<Texture>> m_textures;
	std::string m_failTexture = "fail.jpg";
};