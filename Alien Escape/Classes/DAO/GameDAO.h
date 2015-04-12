#ifndef GAMEDAO_H
#define GAMEDAO_H

#include "StoryPoint.h"
#include "tinyxml2.h"

#define XMLDOC "Config.xml"

class IGameDAO
{
public:
	virtual ~IGameDAO(){};

	//create
	virtual void create() = 0;

	//read
	virtual std::shared_ptr<std::vector<StoryPoint>> read() = 0;

	//update
	virtual void update(std::shared_ptr<std::vector<StoryPoint>> storyPoints) = 0;

	//delete
	virtual void del() = 0;
private:

};


//xml implementation
class GameDAO : public IGameDAO
{
public:
	virtual ~GameDAO(){};

	//create
	void create();

	//read
	std::shared_ptr<std::vector<StoryPoint>> read();

	//update
	void update(std::shared_ptr<std::vector<StoryPoint>> storyPoints);

	//delete
	void del();
private:

};



#endif