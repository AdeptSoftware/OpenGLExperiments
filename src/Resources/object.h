#pragma once
#include <memory>
#include <glad/glad.h>
#include "glm/glm.hpp"


class CObject {
public:
	~CObject();
	CObject(GLfloat* pVertex, GLuint uBytesCount, GLboolean bFree = true);
	void Position(glm::vec3 pos, GLboolean bOffset = false);
	void Rotate(glm::vec3 angle, GLboolean bOffset = false);
	void Scale(glm::vec3 scale, GLboolean bOffset = false);

	glm::mat4 GetModelMatrix();

	GLuint GetVertexCount();
	GLuint GetBytesCount();

	operator GLfloat* ();

private:
	glm::vec3 m_pos, m_angle, m_scale;
	GLuint m_uBytesCount;
	GLboolean m_bFree;
	GLfloat* m_pData;
};