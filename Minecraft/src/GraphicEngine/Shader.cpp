#include "Shader.h"
#include "GLerror.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

Shader::Shader(const std::string& filepath) 
	: m_FilePath(filepath), m_RendererID(0)
{
	ShaderProgramSource source = ParseShader(filepath);
	m_RendererID = CreateShader(source.VertexSource, source.FragmentSource, source.GeometrySource);
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RendererID));
}

ShaderProgramSource Shader::ParseShader(const std::string &filepath) {
  std::ifstream stream(filepath);
  enum class ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1, GEOMETRY = 2};

  ShaderType type = ShaderType::NONE;
  std::string line;
  std::stringstream ss[3];
  while (std::getline(stream, line)) {
    if (line.find("#shader") != std::string::npos) {
      if (line.find("vertex") != std::string::npos) {
        type = ShaderType::VERTEX;
      }
      else if (line.find("fragment") != std::string::npos) {
        type = ShaderType::FRAGMENT;
	  }
	  else if (line.find("geometry") != std::string::npos) {
		type = ShaderType::GEOMETRY;
	  }
    } else {
      ss[(int)type] << line << "\n";
    }
  }
  return {ss[0].str(), ss[1].str(), ss[2].str()};
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

		char* message = (char*)malloc(length * sizeof(char));
		std::string shaderPart = "";
		if (type == GL_VERTEX_SHADER) {
			shaderPart = "vertex";
		}
		else if(type == GL_FRAGMENT_SHADER) {
			shaderPart = "fragment";
		}
		else if (type == GL_GEOMETRY_SHADER) {
			shaderPart = "geometry";
		}

		glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Error in: " << m_FilePath << std::endl;
		std::cout << "Failed to compile  " << shaderPart  << " shader!" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}
	return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader, const std::string& geometryShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
	unsigned int gs = 0;
	if (geometryShader != "") {
		gs = CompileShader(GL_GEOMETRY_SHADER, geometryShader);
		glAttachShader(program, gs);
	}


	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);
	int result;
	glGetProgramiv(program, GL_LINK_STATUS, &result);
	if (result == GL_FALSE) {
		int length = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)malloc(length * sizeof(char));
		glGetProgramInfoLog(program, length, &length, message);
		std::cout << "Failed to link program" << std::endl;
                if ( length == 0 ) {
                  std::cout << "No further inFormsation provided" << std::endl;
                }
		std::cout << message << std::endl;
		glDeleteProgram(program);
		return 0;
	}
	glValidateProgram(program);

	glGetProgramiv(program, GL_VALIDATE_STATUS, &result);
	if (result == GL_FALSE) {
		int length = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)malloc(length * sizeof(char));
		glGetProgramInfoLog(program, length, &length, message);
		std::cout << "Failed to validate program" << std::endl;
                if ( length == 0 ) {
                  std::cout << "No further inFormsation provided" << std::endl;
                }
		std::cout << message << std::endl;
		glDeleteProgram(program);
		return 0;
	}

	glDeleteShader(vs); 
	glDeleteShader(fs);
	if (geometryShader != "")
		glDeleteShader(gs); 

	return program;
}

void Shader::Bind() const
{
	GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

void Shader::SetUniform1uiv(const std::string& name, GLuint* v, int count)
{
	GLCall(glUniform1uiv(GetUniformLocation(name), count, v));
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1f(const std::string& name, float value)
{
	GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
{
	GLCall(glUniform3f(GetUniformLocation(name), v0, v1, v2));
}


void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniformMat4f(const std::string& name, glm::mat4 matrix) {
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
	if (location == -1) {
          std::cout << "In file: " << m_FilePath << std::endl;
          std::cout << "Warning : uniForms '" << name << "' doesn't exist or may not be used in the shaders!" << std::endl;
        }
		
	m_UniformLocationCache[name] = location;
	return location;
}
