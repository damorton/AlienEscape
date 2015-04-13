/*
Scene.h

Scene is an abstract class and outlines the funstions
needed for all scenes in the game.

@author	David Morton K00179391
@date	13.4.15
*/
//Includes
#ifndef SCENE_H_
#define SCENE_H_

//Scene state management
enum SceneState{ RUNNING, PAUSED, DESTROY };

class Scene{
public:	

	//Pure virutal functions
	virtual bool init() = 0;
	virtual bool run() = 0;
	virtual void cleanup() = 0;	
	virtual void pause() = 0;	
	virtual bool loadMedia() = 0;

	/*
		Check the scenes status

		@return bool scene paused
	*/
	bool isPaused(){ if (thisSceneState == PAUSED) return true; else return false; };
protected:
	bool initCompleted;
	SceneState thisSceneState;	
};
#endif