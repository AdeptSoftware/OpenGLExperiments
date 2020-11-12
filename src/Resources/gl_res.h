#pragma once // Абстрактный базовый класс ресурсов
#include <string>
#include <glad/glad.h>

#define string			std::string

class _CGLResource {
public:
	GLuint ID() const { return m_uID; }

protected:
	GLuint m_uID = 0;
};

class CResourceManager;

class CGLResource : public _CGLResource {
	friend CResourceManager;
public:
	virtual void Activate() = 0;

protected:
	virtual void Delete() = 0;
};