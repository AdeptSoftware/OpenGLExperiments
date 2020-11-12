#include "VertexArraysObject.h"


CVertexArraysObject::CVertexArraysObject(GLenum target, GLsizei nVBOCount) {
	glGenVertexArrays(1, &m_uID);
	m_vboID.clear();
	m_target = target;
	m_uAttributeIndex = 0;
	m_vboID.resize(nVBOCount);
	glGenBuffers(nVBOCount, m_vboID.data());
	glBindVertexArray(m_uID);
	m_uIndex = 0;
}

CVertexArraysObject::~CVertexArraysObject() {
	Delete();
}

void CVertexArraysObject::Bind(void* data, GLuint bytes, GLenum data_type, GLuint v_size, GLenum usage, GLboolean normalized) {
	Bind(data, bytes, usage);
	Attribute(data_type, v_size, usage);
}

void CVertexArraysObject::Bind(void* data, GLuint bytes, GLenum usage) {
	if (m_uIndex >= m_vboID.size())
		throw string("No free slots for VBO!");
	glBindBuffer(m_target, m_vboID[m_uIndex]);
	glBufferData(m_target, bytes, data, usage);
	m_uIndex++;
}

void CVertexArraysObject::Attribute(GLenum data_type, GLuint v_size, GLboolean normalized, GLsizei stride, const void* ptr) {
	glVertexAttribPointer(m_uAttributeIndex, v_size, data_type, normalized, stride, ptr);
	glEnableVertexAttribArray(m_uAttributeIndex);
	m_uAttributeIndex++;
}

void CVertexArraysObject::Activate() {
	glBindVertexArray(m_uID);
}

void CVertexArraysObject::Delete() {
	glDeleteBuffers(m_vboID.size(), m_vboID.data());
	glDeleteVertexArrays(1, &m_uID);
	m_vboID.clear();
}