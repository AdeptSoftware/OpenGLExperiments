#pragma once
#include <vector>
#include "gl_res.h"

class CVertexArraysObject : public CGLResource {
public:
	CVertexArraysObject(GLenum target = GL_ARRAY_BUFFER, GLsizei nVBOCount = 1);
	~CVertexArraysObject();

	// bytes - количество байт массива data;
	// v_size - количество элементов в векторе (3 = x, y, z).
	// usage - это ожидаемый шаблон использования данных (GL_STATIC_DRAW, ...)
	void Bind(void* data, GLuint bytes, GLenum usage = GL_STATIC_DRAW);
	void Bind(void* data, GLuint bytes, GLenum data_type, GLuint v_size, GLenum usage = GL_STATIC_DRAW, GLboolean normalized = GL_FALSE);
	void Attribute(GLenum data_type, GLuint v_size, GLboolean normalized = GL_FALSE, GLsizei stride = 0, const void* ptr = nullptr);

	virtual void Activate();
protected:
	GLuint m_uIndex = 0;
	GLuint m_uAttributeIndex = 0;
	GLenum m_target = GL_ARRAY_BUFFER;
	std::vector<GLuint> m_vboID;
	virtual void Delete();
};