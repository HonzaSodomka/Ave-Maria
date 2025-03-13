#pragma once

class FrameCounter
{
public:
	FrameCounter();

	bool hasSecondPassed();
	int getNumberOfFrames();
	void setNumberOfFrames(int);
private:
	double previousTime;
	double currentTime;
	int frameCount;
};

