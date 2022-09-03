#include "hzpch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

namespace Hazel
{
	OpenGLShader::OpenGLShader(const std::string& vertSrc, const std::string& fragSrc)
	{
		int vertShader = CompileShader(GL_VERTEX_SHADER, vertSrc);
		int fragShader = CompileShader(GL_FRAGMENT_SHADER, fragSrc);

		id = glCreateProgram();

		glAttachShader(id, vertShader);
		glAttachShader(id, fragShader);

		glLinkProgram(id);

		int isLinked = 0;
		glGetProgramiv(id, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE)
		{
			int maxLength = 0;
			glGetProgramiv(id, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> infoLog(maxLength);

			glDeleteProgram(id);

			glDeleteShader(vertShader);
			glDeleteShader(fragShader);

			HZ_CORE_ERROR("{0}", infoLog.data());
			HZ_CORE_ASSERT(false, "Shader link failure!");
		}

		glDetachShader(id, vertShader);
		glDetachShader(id, fragShader);
	}
	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(id);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(id);
	}
	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	const int& OpenGLShader::GetLocation(const std::string& name) { return glGetUniformLocation(id, name.c_str()); }

	void OpenGLShader::SetUniformFloat(const std::string& name, const float& f) { glUniform1f(GetLocation(name), f); }
	void OpenGLShader::SetUniformFloat2(const std::string& name, const glm::vec2& f2) { glUniform2f(GetLocation(name), f2.x, f2.y); }
	void OpenGLShader::SetUniformFloat3(const std::string& name, const glm::vec3& f3) { glUniform3f(GetLocation(name), f3.x, f3.y, f3.z); }
	void OpenGLShader::SetUniformFloat4(const std::string& name, const glm::vec4& f4) { glUniform4f(GetLocation(name), f4.x, f4.y, f4.z, f4.w); }

	void OpenGLShader::SetUniformInt(const std::string& name, const int& i) { glUniform1i(GetLocation(name), i); }
	void OpenGLShader::SetUniformInt2(const std::string& name, const glm::ivec2& i2) { glUniform2i(GetLocation(name), i2.x, i2.y); }
	void OpenGLShader::SetUniformInt3(const std::string& name, const glm::ivec3& i3) { glUniform3i(GetLocation(name), i3.x, i3.y, i3.z); }
	void OpenGLShader::SetUniformInt4(const std::string& name, const glm::ivec4& i4) { glUniform4i(GetLocation(name), i4.x, i4.y, i4.z, i4.w); }

	void OpenGLShader::SetUniformMat2f(const std::string& name, const glm::mat2& m2) { glUniformMatrix3fv(GetLocation(name), 1, GL_FALSE, &m2[0][0]); }
	void OpenGLShader::SetUniformMat3f(const std::string& name, const glm::mat3& m3) { glUniformMatrix3fv(GetLocation(name), 1, GL_FALSE, &m3[0][0]); }
	void OpenGLShader::SetUniformMat4f(const std::string& name, const glm::mat4& m4) { glUniformMatrix4fv(GetLocation(name), 1, GL_FALSE, &m4[0][0]); }

	void OpenGLShader::SetUniformBool(const std::string& name, const bool& b) { glUniform1i(GetLocation(name), b); }

	int OpenGLShader::CompileShader(const int shaderType, const std::string& shaderSrc)
	{
		int shader = glCreateShader(shaderType);
		const char* src = shaderSrc.c_str();

		glShaderSource(shader, 1, &src, 0);
		glCompileShader(shader);

		int isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			int maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> infoLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
			glDeleteShader(shader);

			HZ_CORE_ERROR("{0}", infoLog.data());
			std::string shaderTypeName = shaderType == GL_VERTEX_SHADER ? "Vertex " : shaderType == GL_FRAGMENT_SHADER ? "Fragment " : "";
			HZ_CORE_ASSERT(false, shaderTypeName + "Shader compilation failure!");
		}
		return shader;
	}
}