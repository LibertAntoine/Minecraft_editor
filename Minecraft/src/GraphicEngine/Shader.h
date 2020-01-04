#pragma once

#include <string>
#include <unordered_map>
#include <GL/glew.h>
#include "glm/glm.hpp"
#include "MinecraftEditor/Graphic/Lights/LightManager.h"

struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
	std::string GeometrySource;
};

class Shader
{
private:
	std::string m_FilePath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	//Set UniFormss
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1uiv(const std::string& name, GLuint* v1, int count);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform3f(const std::string& name, float v0, float v1, float v2);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, glm::mat4 matrix);
private : 
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader, const std::string& geometryShader);
	int GetUniformLocation(const std::string& name);
};
