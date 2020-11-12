#include "Object.h"
#include "glm/gtc/matrix_transform.hpp"

CObject::~CObject() {
	if (m_bFree && !m_pData)
		delete[] m_pData;
}

CObject::CObject(GLfloat* pData, GLuint uBytesCount, GLboolean bFree) {
	m_scale = glm::vec3(1.0f, 1.0f, 1.0f);
	m_pos   = glm::vec3(0.0f, 0.0f, 0.0f);
	m_angle = glm::vec3(0.0f, 0.0f, 0.0f);
	m_uBytesCount = uBytesCount;
	m_pData = pData;
	m_bFree = bFree;
}

void CObject::Position(glm::vec3 pos, GLboolean bOffset) {
	if (bOffset)	m_pos += pos;
	else			m_pos  = pos;
}

void CObject::Rotate(glm::vec3 angle, GLboolean bOffset) {
	if (bOffset)	m_angle += angle;
	else			m_angle  = angle;
}

void CObject::Scale(glm::vec3 scale, GLboolean bOffset) {
	if (bOffset)	m_scale += scale;
	else			m_scale  = scale;
}

glm::mat4 CObject::GetModelMatrix() {
	glm::mat4 model = glm::mat4(1.0f);
	if (m_pos.x != 0.0f || m_pos.y != 0.0f || m_pos.z == 0.0f)
		model = glm::translate(glm::mat4(1.0f), m_pos);
	if (m_angle.x != 0.0f)
		model = glm::rotate(model, m_angle.x, glm::vec3(1.0f, 0.0f, 0.0f));
	if (m_angle.y != 0.0f)
		model = glm::rotate(model, m_angle.y, glm::vec3(0.0f, 1.0f, 0.0f));
	if (m_angle.z != 0.0f)
		model = glm::rotate(model, m_angle.z, glm::vec3(0.0f, 0.0f, 1.0f));
	if (m_scale.x != 1.0f || m_scale.y != 1.0f || m_scale.z != 1.0f)
		model = glm::scale(model, m_scale);
	return model;
}

GLuint CObject::GetVertexCount() {
	return m_uBytesCount / sizeof(GLfloat) / 3;
}

GLuint CObject::GetBytesCount() {
	return m_uBytesCount;
}

CObject::operator GLfloat* () {
	return m_pData;
}