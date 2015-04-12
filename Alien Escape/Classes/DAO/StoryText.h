#ifndef _STORY_TEXT_
#define _STORY_TEXT_
#include "TextItem.h"

class StoryText : public TextItem 
{
public:
	StoryText(){}
	StoryText(std::string thisText){setText(thisText.c_str());}
	~StoryText(){}

	
	
	
private:
	

	
};


#endif