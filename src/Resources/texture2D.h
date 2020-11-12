#pragma once
#include "gl_res.h"


class CTexture2D : public CGLResource {
public:
	CTexture2D(const unsigned char* data, GLenum mode, GLuint uWidth, GLuint uHeight, GLenum filter, GLenum wrap_mode);

	CTexture2D& operator=(CTexture2D&&) = delete;
	CTexture2D(const CTexture2D&) = delete;
	CTexture2D(CTexture2D&&) = delete;

	~CTexture2D();

	virtual void Activate();
private:
	virtual void Delete();

	GLenum m_uMode   = GL_RGBA;
	GLuint m_uWidth  = 0;
	GLuint m_uHeight = 0;
};