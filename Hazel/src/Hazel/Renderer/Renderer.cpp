#include "hzpch.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Hazel
{
	RendererAPI::API RendererAPI::api = RendererAPI::API::OpenGL;
	RendererAPI* RendererAPI::instance = new OpenGLRendererAPI;
	Renderer::SceneData* Renderer::sceneData = new Renderer::SceneData;

	void Renderer::BeginScene(Camera& camera) 
	{
		sceneData->viewProj = camera.GetViewProj();
	}
	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->SetUniformMat4f("u_ViewProj", sceneData->viewProj);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->SetUniformMat4f("u_Transform", transform);
		vertexArray->Bind();
		RendererAPI::DrawIndexed(vertexArray);
	}
}