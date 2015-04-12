#ifndef _TEXT_ITEM_
#define _TEXT_ITEM_
#include <string>

class TextItem 
{
public:
	TextItem(){}
	TextItem(std::string thisText){text = thisText;}
	~TextItem(){}

	std::string getText(){return text;}
	void setText(const char* newText){text.assign(newText);}
	
	
private:
	std::string text;

	
};


#endif