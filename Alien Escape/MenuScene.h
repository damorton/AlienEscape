#ifndef MENUSCENE_H
#define MENUSCENE_H

#include "Scene.h"

class MenuScene : public  Scene
{
public:
	MenuScene();
	virtual ~MenuScene();
	virtual bool init();
	virtual bool run();
	virtual void cleanup();
	virtual bool loadMedia();
	
private:

};



#endif