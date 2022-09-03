#pragma once
#include "Hazel/Renderer/Shader.h"

#include <glm/glm.hpp>
#include <string>

namespace Hazel
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertSrc, const std::string& fragSrc);
		~OpenGLShader() override;

		void Bind() const override;
		void Unbind() const override;

		const int& GetLocation(const std::string& name);

		void SetUniformFloat(const std::string& name, const float& f);
		void SetUniformFloat2(const std::string& name, const glm::vec2& f2);
		void SetUniformFloat3(const std::string& name, const glm::vec3& f3);
		void SetUniformFloat4(const std::string& name, const glm::vec4& f4);

		void SetUniformInt(const std::string& name, const int& i);
		void SetUniformInt2(const std::string& name, const glm::ivec2& i2);
		void SetUniformInt3(const std::string& name, const glm::ivec3& i3);
		void SetUniformInt4(const std::string& name, const glm::ivec4& i4);

		void SetUniformMat2f(const std::string& name, const glm::mat2& m2);
		void SetUniformMat3f(const std::string& name, const glm::mat3& m3);
		void SetUniformMat4f(const std::string& name, const glm::mat4& m4);

		void SetUniformBool(const std::string& name, const bool& b);

	private:
		uint32_t id;
		static int CompileShader(const int type, const std::string& shaderSrc);
	};
}