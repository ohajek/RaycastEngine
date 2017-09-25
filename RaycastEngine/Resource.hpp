#pragma once
#include <string>
#include <iostream>

#include "Texture.hpp"

template<typename T>
class Resource {
public:
	Resource() {
		std::cout << "Creating resource" << std::endl;
		m_resource = std::make_shared<T>();
	}

	~Resource() {
		std::cout << "Deleting resource" << m_resource.use_count() << std::endl;
	}
	
	Resource(const Resource& other) {
		m_handle = other.m_handle;
		m_name = other.m_name;
		m_filename = other.m_filename;
		m_path = other.m_path;
		m_resource = other.m_resource;
		std::cout << "Copy constr" << std::endl;
	}
	
	bool loadFromFile(const std::string& filename) {
		if (!m_resource->loadFromFile(filename)) {
			return false;
		}
		return true;
	}

	unsigned int getHandle() {
		return m_handle;
	}

	std::string getName() {
		return m_name;
	}

	std::string getFilename() {
		return m_filename;
	}

	std::string getPath() {
		return m_path;
	}

	unsigned int getRefCount() {
		return m_refCount;
	}

	T* operator->() {
		return m_resource.get();
	}

private:
	//T* m_resource;
	std::shared_ptr<T> m_resource;
	unsigned int m_handle;
	std::string m_name;
	std::string m_filename;
	std::string m_path;
};