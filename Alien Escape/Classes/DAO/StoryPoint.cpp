#include "StoryPoint.h"

StoryPoint::StoryPoint()
{
	choices = std::shared_ptr<std::vector<StoryChoice>>(new std::vector<StoryChoice>());
}

StoryPoint::~StoryPoint()
{

}


void StoryPoint::addFilePath(const char* name, const char* storyChoice)
{	
	choices->push_back(StoryChoice(std::string(name), std::string(storyChoice)));
}


std::shared_ptr<std::vector<StoryChoice>> StoryPoint::getStoryChoices()
{
	return choices;
}