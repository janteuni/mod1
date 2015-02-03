#ifndef _TimeManager_H
#define _TimeManager_H

# include <chrono>
# include <iostream>
# include <thread>


class TimeManager
{
	public:

		~TimeManager(void);

		static TimeManager& Instance()
		{
			static TimeManager instance;
			return instance;
		}

		double 		CalculateFrameRate(bool writeToConsole);
		double 		GetTime();
		void 		Sleep(int milliseconds);

		double 		DeltaTime = 0;
		double 		CurrentTime = 0;

	private:
		TimeManager(void);
		TimeManager(TimeManager const & ref);
		TimeManager & operator=(TimeManager const & ref);
};

#endif
