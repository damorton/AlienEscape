/*
Record.cpp

Record for storing groups of resources 

@author	David Morton K00179391, James Daly L.I.T
@date	13.4.15
*/
#include "Record.h"

Record::Record()
{
	//Create a vector of resources inside record
	resources = std::shared_ptr<std::vector<Resource>>(new std::vector<Resource>());
}

Record::~Record()
{

}


void Record::addResource(const char* name, const char* resource)
{	
	//Add resource to record
	resources->push_back(Resource(std::string(name), std::string(resource)));
}


std::shared_ptr<std::vector<Resource>> Record::getResources()
{
	return resources;
}