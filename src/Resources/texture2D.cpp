#include "texture2D.h"


CTexture2D::CTexture2D(const unsigned char* data, GLenum mode, GLuint uWidth, GLuint uHeight, GLenum filter, GLenum wrap_mode) {
	m_uHeight = uHeight;
	m_uWidth = uWidth;
    m_uMode = mode;

	glGenTextures(1, &m_uID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_uID);
    glTexImage2D(GL_TEXTURE_2D, 0, mode, uWidth, uHeight, 0, mode, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_mode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_mode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
}

CTexture2D::~CTexture2D() {
    Delete();
}

void CTexture2D::Delete() {
    glDeleteTextures(1, &m_uID);
}

void CTexture2D::Activate() {
    glBindTexture(GL_TEXTURE_2D, m_uID);
}
