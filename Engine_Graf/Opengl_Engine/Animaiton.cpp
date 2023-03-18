#include "Animaiton.h"

#include "Timer.h"


#include <iostream>

DllExport Animation::Animation()
{
}

DllExport Animation::~Animation()
{
}

DllExport void Animation::UpdateAnimation(float durationInSecs) 
{
	currentTime += Timer::getTimer()->timeBetweenFrames() * framesPerSeconds;

	std::cout << currentTime << std::endl;

	while (currentTime > durationInSecs)
	{
		currentTime -= durationInSecs;
	}

	currentIndex = static_cast<int>((int)(currentTime * framesPerSeconds));
}

DllExport void Animation::addFrame(float frameX, float frameY, float frameWidth, float frameHeigth, float textureWidth, float textureHeigth, float animationSpeed)
{
	//----------------------------------------------------------------
	Frame frame;

	frame.uvCoords[0].u = (frameX / textureWidth);
	frame.uvCoords[0].v = (frameY / textureHeigth);
	//----------------------------------------------------------------
	frame.uvCoords[1].u = ((frameX + frameWidth) / textureWidth);
	frame.uvCoords[1].v = (frameY / textureHeigth);
	//----------------------------------------------------------------
	frame.uvCoords[2].u = (frameX / textureWidth);
	frame.uvCoords[2].v = ((frameY + frameHeigth) / textureHeigth);
	//----------------------------------------------------------------
	frame.uvCoords[3].u = ((frameX + frameWidth) / textureWidth);
	frame.uvCoords[3].v = ((frameY + frameHeigth) / textureHeigth);
	//----------------------------------------------------------------
	framesVector.push_back(frame);

	framesPerSeconds = framesVector.size();
}

DllExport void Animation::addFrame(float frameX, float frameY, float frameWidth, float frameHeigth, float textureWidth, float textureHeigth, float animationSpeed, int frameCount)
{
	float frameXIndex = 0;

	for (int i = 0; i < frameCount; i++) {
		Frame frame;

		frame.uvCoords[0].u = ((frameX + frameXIndex) / textureWidth);
		frame.uvCoords[0].v = (frameY / textureHeigth);
		//-----------------------------------------------------------------------------
		frame.uvCoords[1].u = (((frameX + frameXIndex) + frameWidth) / textureWidth);
		frame.uvCoords[1].v = (frameY / textureHeigth);
		//-----------------------------------------------------------------------------
		frame.uvCoords[2].u = ((frameX + frameXIndex) / textureWidth);
		frame.uvCoords[2].v = ((frameY + frameHeigth) / textureHeigth);
		//-----------------------------------------------------------------------------
		frame.uvCoords[3].u = (((frameX + frameXIndex) + frameWidth) / textureWidth);
		frame.uvCoords[3].v = ((frameY + frameHeigth) / textureHeigth);
		//-----------------------------------------------------------------------------

		framesVector.push_back(frame);
		frameXIndex += frameWidth;
	}

	framesPerSeconds = framesVector.size();
}

DllExport int Animation::getCurrentIndex()
{
	return currentIndex;
}

DllExport std::vector<Frame>& Animation::getFrames()
{
	return framesVector;
}
