#pragma once
#include <string>

class FrameCounter
{
public:
	FrameCounter();

	bool hasSecondPassed();
	int getNumberOfFrames();
	int getLastNumberOfFrames();
	void setNumberOfFrames(int);
private:
	double previousTime;
	double currentTime;
	int frameCount;
	int lastFrameCount;
};

