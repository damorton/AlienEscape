/*
GameDAO.h

Data Access Object for reading and writing to XML file

@author	David Morton K00179391, James Daly L.I.T
@date	13.4.15
*/
#ifndef GAMEDAO_H
#define GAMEDAO_H

#include "../Definitions.h"
#include "Record.h"
#include "tinyxml2.h"

//Abstartct Class/Interface for GameDAO
class IGameDAO
{
public:
	virtual ~IGameDAO(){};

	//Create
	virtual void create() = 0;

	//Read
	virtual std::shared_ptr<std::vector<Record>> read() = 0;

	//Update
	virtual void update(std::shared_ptr<std::vector<Record>> resources) = 0;

	//Delete
	virtual void del() = 0;
private:

};


//XML implementation
class GameDAO : public IGameDAO
{
public:
	virtual ~GameDAO(){};

	//Create the configuration file 
	void create();

	/*
		Read all records from the configuration file

		@return vector<Record> vector of records from the config file
	*/
	std::shared_ptr<std::vector<Record>> read();

	/*
		Write configuration info to XML file

		@param std::vector<Record>> resources vector of records
	*/
	void update(std::shared_ptr<std::vector<Record>> resources);

	/*
		Delete records from the XML file
	*/
	void del();
private:

};

#endif