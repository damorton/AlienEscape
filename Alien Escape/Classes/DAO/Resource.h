/*
Resource.h

Resource for storing information in XML file

@author	David Morton K00179391, James Daly L.I.T
@date	13.4.15
*/
#ifndef RESOURCE_H
#define RESOURCE_H
#include "TextItem.h"

class Resource : public TextItem 
{
public:	
	Resource(){}

	/*
		Overloaded constructor for creating and initializing the resource

		@param string name, the name of the resource
		@param string thisText, the value stored in the resource
	*/
	Resource(std::string name, std::string thisText){ setName(name.c_str()); setValue(thisText.c_str()); }

	~Resource(){}		
};


#endif