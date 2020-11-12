#pragma once
#include <map>
#include <memory>
#include "texture2D.h"
#include "shader_program.h"
#include "VertexArraysObject.h"


class CResourceManager {
public:
	~CResourceManager();
	CResourceManager(string sExeFileName, GLboolean bCheckName = true);

	void Attach(string sResourceName, CGLResource* pResource);
	void Detach(CGLResource* pRes);

	CTexture2D* Texture2D(string sResourceName, string sTextureFileName);
	CShaderProgram* ShaderProgram(string sResourceName, const char* sVertexShaderData, const char* sFragmentShaderData);
	CShaderProgram* ShaderProgramF(string sResourceName, string sVertexShaderFileName, string sFragmentShaderFileName);

	CGLResource* operator[](string sResourceName);
	string GetResourceName(CGLResource* pRes);

private:
	GLboolean m_bCheckName = true;
	string m_sResourcePath;
	char m_slash = '\\';

	// struct COMPARE_STRING { bool operator()(const char* a, const char* b) const { return strcmp(a, b) < 0; } };

	std::map<string, CGLResource*> m_res;

	char* LoadShader(string sFileName);
	void CheckName(string sResourceName);
	string FullPath(string sFolder, string sFileName);
};