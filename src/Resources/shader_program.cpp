#include "shader_program.h"


CShader::CShader(const char* data, GLenum type, GLsizei count) {
    m_uID = CompileShader(data, type, count);
    // Проверим успешность компиляции шейдера
    GLint nSuccess;
    glGetShaderiv(m_uID, GL_COMPILE_STATUS, &nSuccess);
    if (!nSuccess) {
        GLchar infoLog[1024]{};
        glGetShaderInfoLog(m_uID, 1024, nullptr, infoLog);
        throw "CompileShader Error: " + string(infoLog);
    }
}

GLuint CShader::CompileShader(const char* data, GLenum type, GLsizei count) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, count, &data, nullptr);
    glCompileShader(shader);
    return shader;
}

CShader::~CShader() {
    glDeleteShader(m_uID);
}

// ======= ========= ========= ========= ========= ========= ========= =========

CShaderProgram::CShaderProgram() {
    m_uID = glCreateProgram();
}

CShaderProgram::~CShaderProgram() {
    Delete();
}

void CShaderProgram::Delete() {
    glDeleteProgram(m_uID);
}

void CShaderProgram::Activate() {
    glUseProgram(m_uID);
}

void CShaderProgram::Init(const CShader& vertex, const CShader& fragment) {
    m_uID = glCreateProgram();
    glAttachShader(m_uID, vertex.ID());
    glAttachShader(m_uID, fragment.ID());
    glLinkProgram(m_uID);
    // Проверим успешность линковки шейдерной программы
    GLint nSuccess;
    glGetProgramiv(m_uID, GL_LINK_STATUS, &nSuccess);
    if (!nSuccess)  {
        GLchar infoLog[1024]{};
        glGetShaderInfoLog(m_uID, 1024, nullptr, infoLog);
        throw "LinkShaderProgram Error: " + string(infoLog);
    }
}

CShaderProgram::CShaderProgram(const CShader& vertex, const CShader& fragment) {
    Init(vertex, fragment);
}

CShaderProgram::CShaderProgram(const char* sVertexShaderData, const char* sFragmentShaderData) {
    CShader vertex(sVertexShaderData, GL_VERTEX_SHADER, 1);
    CShader fragment(sFragmentShaderData, GL_FRAGMENT_SHADER, 1);
    Init(vertex, fragment);
}

void CShaderProgram::Set(const GLchar* sVariableName, GLint nValue) {
    glUniform1i(glGetUniformLocation(m_uID, sVariableName), nValue);
}

void CShaderProgram::Set(const GLchar* sVariableName, const GLfloat* matrix) {
    GLint location = glGetUniformLocation(m_uID, sVariableName);
    glUniformMatrix4fv(location, 1, GL_FALSE, matrix);
}