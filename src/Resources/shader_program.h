#pragma once
#include "gl_res.h"


class CShader : public _CGLResource {
public:
	~CShader();
	CShader(const char* data, GLenum type, GLsizei count = 1);
	static GLuint CompileShader(const char* data, GLenum type, GLsizei count = 1);
};


class CShaderProgram : public CGLResource {
public:
	CShaderProgram();
	~CShaderProgram();
	CShaderProgram(const CShader& vertex, const CShader& fragment);
	CShaderProgram(const char* sVertexShaderData, const char* sFragmentShaderData);

	CShaderProgram(CShaderProgram&&) = delete;
	CShaderProgram(const CShaderProgram&) = delete;

	void Set(const GLchar* sVariableName, GLint nValue);
	void Set(const GLchar* sVariableName, const GLfloat* matrix);

	virtual void Activate();
private:
	virtual void Delete();
	void Init(const CShader& vertex, const CShader& fragment);
};