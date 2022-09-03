#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Hazel
{
	class HAZEL_API Layer
	{
	public:
		Layer(const std::string& name = "Layer") 
			: name(name) {};
		virtual ~Layer() {};

		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnUpdate() {};
		virtual void OnImGuiRender() {};
		virtual void OnEvent(Event& e) {};

		const std::string& GetName() const { return name; }
	private:
		std::string name;
	};
}