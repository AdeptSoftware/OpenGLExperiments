#include "res_manager.h"
#include <fstream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


string CResourceManager::FullPath(string sFileName, string sFolder) {
	return m_sResourcePath + sFolder + m_slash + sFileName;
}

char* CResourceManager::LoadShader(string sFileName) {
	std::ifstream f(FullPath(sFileName, "shaders"));
	if (f.is_open()) {
		// Получаем размер файла
		f.seekg(0, std::ios_base::end);
		unsigned long long size = f.tellg();
		f.seekg(std::ios_base::beg);
		// Копируем содержимое файла
		char* buf = new char[size + 1];
		memset(buf, 0, size + 1);
		f.read(buf, size);
		f.close();
		return buf;
		// return std::shared_ptr<char>(buf, std::default_delete<char[]>());
	}
	else
		throw "Shader not found: " + FullPath(sFileName, "shaders");
	return nullptr;
}

CResourceManager::CResourceManager(string sExeFileName, GLboolean bCheckName) {
	int i = sExeFileName.find_last_of("\\/");
	if (i == sExeFileName.npos)
		throw "String \"" + sExeFileName + "\" doesn't contain slash!";
	m_slash = sExeFileName[i];
	m_bCheckName = bCheckName;
	i++;
	m_sResourcePath = sExeFileName.substr(0, i) + "res" + m_slash;
}

void CResourceManager::CheckName(string sResourceName) {
	if (m_bCheckName) {
		auto it = m_res.find(sResourceName);
		if (it != m_res.end())
			throw "Resource name \"" + sResourceName + "\" is already taken!";
	}
}

CTexture2D* CResourceManager::Texture2D(string sResourceName, string sTextureFileName) {
	CheckName(sResourceName);
	// Начнем загрузку пикчи
	int w, h, channels;
	stbi_set_flip_vertically_on_load(true);
	string sFileName = FullPath(sTextureFileName, "textures").c_str();
	unsigned char* data = stbi_load(sFileName.c_str(), &w, &h, &channels, 0);
	if (!data)
		throw "Texture \"" + sFileName + "\" not found!";
	GLenum mode = (channels == 4 ? GL_RGBA : GL_RGB);
	CTexture2D* pRes = new CTexture2D(data, mode, w, h, GL_NEAREST, GL_CLAMP_TO_EDGE);
	m_res.emplace(sResourceName, pRes);
	return pRes;
}

CShaderProgram* CResourceManager::ShaderProgram(string sResourceName, const char* sVertexShaderData, const char* sFragmentShaderData) {
	CheckName(sResourceName);
	CShaderProgram* pRes = new CShaderProgram(sVertexShaderData, sFragmentShaderData);
	m_res.emplace(sResourceName, pRes); // std::shared_ptr<CGLResource>((CGLResource*)pRes));
	return pRes;
}

CShaderProgram* CResourceManager::ShaderProgramF(string sResourceName, string sVertexShaderFileName, string sFragmentShaderFileName) {
	CheckName(sResourceName);
	char* vertex_data = LoadShader(sVertexShaderFileName);
	char* fragment_data = LoadShader(sFragmentShaderFileName);
	CShaderProgram* pRes = ShaderProgram(sResourceName, vertex_data, fragment_data);
	delete[] fragment_data;
	delete[] vertex_data;
	return pRes;
}

void CResourceManager::Attach(string sResourceName, CGLResource* pResource) {
	m_res.emplace(sResourceName, pResource);
}

void CResourceManager::Detach(CGLResource* pRes) {
	if (pRes == nullptr)
		throw string("Resource pointer is null!");
	for (auto it = m_res.begin(); it != m_res.end(); it++) {
		if (it->second->ID() == pRes->m_uID) {
			m_res.erase(it);
			pRes->Delete();
			delete pRes;
			return;
		}
	}
	char buf[16];
	_itoa_s(pRes->m_uID, buf, 16, 10);
	throw "Resource ID =" + string(buf) + " not found!";
}

CGLResource* CResourceManager::operator[](string sResourceName) {
	auto it = m_res.find(sResourceName);
	if (it == m_res.end())
		return nullptr;
	return it->second;
}

string CResourceManager::GetResourceName(CGLResource* pRes) {
	for (auto it = m_res.begin(); it != m_res.end(); it++) {
		if (it->second->ID() == pRes->m_uID)
			return it->first;
	}
	return "";
}

CResourceManager::~CResourceManager() {
	for (auto it = m_res.begin(); it != m_res.end(); it++) {
		it->second->Delete();
		delete it->second;
	}
	m_res.clear();
}