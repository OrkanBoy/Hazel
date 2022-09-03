#include "Hazel.h"
#include "imgui.h"
#include "Platform/Windows/WindowsInput.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Platform/OpenGL/OpenGLShader.h"

class ExampleLayer : public Hazel::Layer
{
public:
	std::shared_ptr<Hazel::Shader> shader;
	std::shared_ptr<Hazel::VertexArray> vertexArray;

	Hazel::Camera camera;
	glm::vec3 squareColor{1.0f, 0.0f, 0.5f};

	ExampleLayer()
		: camera(Hazel::Application::Get().GetWindow().GetWidth() / 500.0f,
			Hazel::Application::Get().GetWindow().GetHeight() / 500.0f,
			glm::vec3(0.0f), 0.0f)
	{
		const char* vertSrc = R"(
		#version 430 core
		layout (location = 0) in vec2 a_Position;

		uniform mat4 u_ViewProj;
		uniform mat4 u_Transform;

		void main()
		{
			gl_Position = u_ViewProj * u_Transform * vec4(a_Position, 0.0, 1.0);
		})";

		const char* fragSrc = R"(
		#version 430 core
		out vec4 color;

		uniform vec3 u_Color;

		void main()
		{
			color = vec4(u_Color, 1.0);
		})";

		vertexArray.reset(Hazel::VertexArray::Create());

		float vertices[]
		{
			-0.5f, -0.5f,
			0.5f, -0.5f,
			0.5f, 0.5f,
			-0.5, 0.5f
		};
		Hazel::BufferLayout layout
		{
			{Hazel::ShaderDataType::Float2, "a_Position"}
		};
		std::shared_ptr<Hazel::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Hazel::VertexBuffer::Create(vertices, layout));
		vertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[]
		{
			0, 1, 2,
			2, 3, 0
		};
		std::shared_ptr<Hazel::IndexBuffer> indexBuffer;
		indexBuffer.reset(Hazel::IndexBuffer::Create(indices));
		vertexArray->SetIndexBuffer(indexBuffer);

		shader.reset(Hazel::Shader::Create(vertSrc, fragSrc));
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Test"); {
			ImGui::ColorEdit3("u_Color", glm::value_ptr(squareColor));
		} ImGui::End();
	}

	void OnUpdate() override
	{

		if (Hazel::Input::IsKeyPressed(HZ_KEY_W))
			camera.SetPosition(camera.GetPosition() + HZ_DELTATIME * glm::vec3(0.0f, 1.0f, 0.0f));
		if (Hazel::Input::IsKeyPressed(HZ_KEY_S))
			camera.SetPosition(camera.GetPosition() - HZ_DELTATIME * glm::vec3(0.0f, 1.0f, 0.0f));
		if (Hazel::Input::IsKeyPressed(HZ_KEY_D))
			camera.SetRotation(camera.GetRotation() + HZ_DELTATIME);
		if (Hazel::Input::IsKeyPressed(HZ_KEY_A))
			camera.SetRotation(camera.GetRotation() - HZ_DELTATIME);

		Hazel::Renderer::BeginScene(camera); {

			shader->Bind();
			std::dynamic_pointer_cast<Hazel::OpenGLShader>(shader)->SetUniformFloat3("u_Color", squareColor);

			Hazel::Renderer::Submit(vertexArray, shader, glm::mat4(1.0f));

		} Hazel::Renderer::EndScene();
	}
};

class Sandbox : public Hazel::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{
	}
};

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}

