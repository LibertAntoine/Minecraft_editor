#pragma once

/**
 * \file Shader.h
 * \brief Manage the shader manipulation.
 * \author Antoine Libert & Nicolas Lienart
 * Vexter, Fragment and Geometry are extract to the same file.
 */

#include <string>
#include <unordered_map>
#include <GL/glew.h>
#include "glm/glm.hpp"

 /**
 * \brief Contains the text of the different shader part.
 */
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

	/**
	* \brief Initialize a new shader line.
	* \param filepath of the file which contains shader line.
	*/
	Shader(const std::string& filepath);
	~Shader();

	/**
	* \brief Bind the Shader program.
	*/
	void Bind() const;

	/**
	* \brief Unbind the Shader program.
	*/
	void Unbind() const;

	// GETTERS - SETTERS //
	/**
	* \brief SetUniformXf/ui/i recup the uniform id in the shader line and load data in it.
	*/
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1uiv(const std::string& name, GLuint* v1, int count);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform3f(const std::string& name, float v0, float v1, float v2);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, glm::mat4 matrix);
	int GetUniformLocation(const std::string& name);

private : 
	/**
	* \brief Manage the creation of the shader program.
	* \param vertexShader text content.
	* \param fragmentShader text content.
	* \param geometryShader text content.
	*/
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader, const std::string& geometryShader);

	/**
	* \brief Parse the file got in the constructor, separate vertex, fragment and geometry part
	*/
	ShaderProgramSource ParseShader(const std::string& filepath);

	/**
	* \brief Compile on the GPU the shader line.
	*/
	unsigned int CompileShader(unsigned int type, const std::string& source);
};
