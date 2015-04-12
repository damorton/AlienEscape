#ifndef _STORY_POINT_
#define _STORY_POINT_

#include "StoryChoice.h"
#include <vector>
#include <memory>

class StoryPoint
{
public:
	StoryPoint();
	~StoryPoint();
	void addFilePath(const char* name, const char* storyChoice);
	std::shared_ptr<std::vector<StoryChoice>> getStoryChoices();
	std::string getName(){ return name; };
	void setName(std::string newName){ name = newName; };
private:	
	std::shared_ptr<std::vector<StoryChoice>> choices;
	std::string name;
};

#endif