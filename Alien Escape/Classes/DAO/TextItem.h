#ifndef _TEXT_ITEM_
#define _TEXT_ITEM_
#include <string>

class TextItem 
{
public:
	TextItem(){}
	TextItem(std::string thisText){ value = thisText; }
	~TextItem(){}

	std::string getValue(){ return value; }
	std::string getName(){ return name; }
	void setValue(const char* newText){ value.assign(newText); }
	void setName(const char* newName){ name.assign(newName); }
	
	
private:
	std::string value;
	std::string name;	
};


#endif