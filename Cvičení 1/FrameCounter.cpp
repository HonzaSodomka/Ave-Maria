#include "FrameCounter.h"
#include <GLFW/glfw3.h>

FrameCounter::FrameCounter()
{
    frameCount = 0;
    previousTime = glfwGetTime();
    currentTime = glfwGetTime();
}

bool FrameCounter::hasSecondPassed()
{
    currentTime = glfwGetTime();
    frameCount++;

    return currentTime - previousTime >= 1.0;
}

int FrameCounter::getNumberOfFrames()
{
    return frameCount;
}

void FrameCounter::setNumberOfFrames(int frames)
{
    frameCount = frames;
    previousTime = glfwGetTime();
}
