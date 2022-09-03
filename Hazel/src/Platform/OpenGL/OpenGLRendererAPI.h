#pragma once
#include "Hazel/Renderer/Renderer.h"

namespace Hazel
{
	class OpenGLRendererAPI : public RendererAPI
	{
	private:
		void SetClearColorImpl(const glm::vec4& color) override;
		void ClearImpl() override;

		void DrawIndexedImpl(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}