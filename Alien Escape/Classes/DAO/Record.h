/*
Record.h

Record for storing groups of resources

@author	David Morton K00179391, James Daly L.I.T
@date	13.4.15
*/
#ifndef RECORD_H
#define RECORD_H

#include "Resource.h"
#include <vector>
#include <memory>

class Record
{
public:
	Record();
	~Record();

	/*
		Add a resource to the record

		@param char* name of the resource 
		@param char* resource being stored 
	*/
	void addResource(const char* name, const char* resource);

	/*
		Get the vector of resources stored in the record

		@return vector<Resource> vector of resources stored in the record
	*/
	std::shared_ptr<std::vector<Resource>> getResources();

	/*
		Get the name of the record

		@return string name of the record
	*/
	std::string getName(){ return name; };

	/*
		Set the name of the record

		@param string newName for the record
	*/
	void setName(std::string newName){ name = newName; };
private:	
	std::shared_ptr<std::vector<Resource>> resources;
	std::string name;
};

#endif