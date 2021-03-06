#include "../include/TimeManager.hpp"

/* ------------- CONSTRUCTOR ----------------------- */

TimeManager::~TimeManager(void)
{
}

TimeManager::TimeManager(void)
{
}


/* ------------- MAIN ----------------------- */

double TimeManager::CalculateFrameRate(bool writeToConsole = false)
{
	static double framesPerSecond = 0.0f;
	static double startTime = GetTime();
	static double lastTime = GetTime();
	//static char strFrameRate[50] = { 0 };
	static double currentFPS = 0.0f;

	CurrentTime = GetTime();
	DeltaTime = CurrentTime - lastTime;
	lastTime = CurrentTime;
	++framesPerSecond;

	if (CurrentTime - startTime > 1.0f) {
		startTime = CurrentTime;
		if (writeToConsole) {
			std::cout << "Current Frames Per Second:" <<  int(framesPerSecond) << std::endl;
		}
		currentFPS = framesPerSecond;
		framesPerSecond = 0;
	}

	return currentFPS;
}


double TimeManager::GetTime()
{
	auto beginningOfTime = std::chrono::system_clock::now().time_since_epoch();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(beginningOfTime).count();
	return ms * 0.001;
}


void TimeManager::Sleep(int ms)
{
	std::this_thread::sleep_for( std::chrono::milliseconds(ms) );
}
