#ifndef SCENE_H_
#define SCENE_H_

enum SceneState{ RUNNING, PAUSED, DESTROY };

class Scene{
public:	
	virtual bool init() = 0;
	virtual bool run() = 0;
	virtual void cleanup() = 0;	
	virtual void pause(){ thisSceneState = PAUSED; };
	virtual void resume(){ thisSceneState = RUNNING; };
	bool isPaused(){ if (thisSceneState == PAUSED) return true; else return false; };

protected:
	bool initCompleted;
	SceneState thisSceneState;	
};




#endif