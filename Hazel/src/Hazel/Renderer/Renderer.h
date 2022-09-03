#pragma once
#include "glm/glm.hpp"

#include "VertexArray.h"
#include "Shader.h"
#include "Camera.h"

namespace Hazel
{
	class RendererAPI 
	{
	public:
		enum class API
		{
			OpenGL, Vulkan, Metal
		};

		static RendererAPI& Get() { return *instance; }
		static API& GetAPI() { return api; }

		static void SetClearColor(const glm::vec4& color) { instance->SetClearColorImpl(color); }
		static void Clear() { instance->ClearImpl(); }

		static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) { instance->DrawIndexedImpl(vertexArray); }

	protected:
		virtual void SetClearColorImpl(const glm::vec4& color) = 0;
		virtual void ClearImpl() = 0;

		virtual void DrawIndexedImpl(const std::shared_ptr<VertexArray>& vertexArray) = 0;

	private:
		static RendererAPI* instance;
		static API api;
	};

	class Renderer
	{
	public:
		static void BeginScene(Camera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform);
		static RendererAPI::API& GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData 
		{
			glm::mat4 viewProj;
		};

		static SceneData* sceneData;
	};
}