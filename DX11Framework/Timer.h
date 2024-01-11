#pragma once
#include <chrono>

using namespace std::chrono;

class Timer
{
	public:
		Timer();

		float GetDelta();
		void Tick();

	private: 
		steady_clock::time_point _lastFrame; 
};

