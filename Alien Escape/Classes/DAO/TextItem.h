/*
TextItem.h

Text string elements for each record and resource

@author	David Morton K00179391, James Daly L.I.T
@date	13.4.15
*/
#ifndef TEXT_ITEM_H
#define TEXT_ITEM_H
#include <string>

class TextItem 
{
public:
	TextItem(){}
	/*
		Overloaded ctor for creating and initializing the text item

		@param string thisText is the string stored in the resource
	*/
	TextItem(std::string thisText){ value = thisText; }
	
	//Deconstructor
	~TextItem(){}

	/*
		Get the value stored in the resource

		@return string value stored in the resource
	*/
	std::string getValue(){ return value; }

	/*
		Get the name of the record/resource

		@return string name of the record/resource
	*/
	std::string getName(){ return name; }

	/*
		Set the value being stored in the resource

		@param char* newText string being stored
	*/
	void setValue(const char* newText){ value.assign(newText); }

	/*
		Set the name of the record/resource

		@param char* newName the name of the record/resource
	*/
	void setName(const char* newName){ name.assign(newName); }		
private:
	std::string value;
	std::string name;	
};


#endif