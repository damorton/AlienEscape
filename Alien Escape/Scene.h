#ifndef SCENE_H_
#define SCENE_H_

enum  SceneState{ RUNNING, PAUSED, DESTROY };

class Scene{
public:
	Scene(); //constructor
	
	virtual bool init();
	virtual bool run();
	virtual void cleanup();
	virtual ~Scene(); //deconstructor
	void pause(){ thisSceneState = PAUSED; };
	void resume(){ thisSceneState = RUNNING; };
	bool isPaused(){ if (thisSceneState == PAUSED) return true; else return false; };

protected:
	bool initCompleted;
	SceneState thisSceneState;	
};




#endif