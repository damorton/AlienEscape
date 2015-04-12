#include "StoryPoint.h"

StoryPoint::StoryPoint()
{
	text = std::shared_ptr<StoryText>(new StoryText());
	choices = std::shared_ptr<std::vector<StoryChoice>>(new std::vector<StoryChoice>());
}

StoryPoint::~StoryPoint()
{

}

void StoryPoint::setStoryText(const char* storyText)
{
	text->setText(storyText);
}


void StoryPoint::addStoryChoice(const char* storyChoice)
{
	
	choices->push_back(StoryChoice(std::string(storyChoice)));
}

std::shared_ptr<StoryText> StoryPoint::getStoryText()
{
	return text;
}

std::shared_ptr<std::vector<StoryChoice>> StoryPoint::getStoryChoices()
{
	return choices;
}