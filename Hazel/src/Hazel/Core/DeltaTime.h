#pragma once

namespace Hazel
{
	class DeltaTime 
	{
	public:

		DeltaTime(float time = 0.0f)
			: time(time) {}

		float GetSeconds() { return time; }
		float GetMilliseconds() { return 1000 * time; }

	private:
		float time;
	};
}