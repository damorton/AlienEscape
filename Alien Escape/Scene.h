#ifndef SCENE_H_
#define SCENE_H_

enum  SceneState{ RUNNING, PAUSED, DESTROY };

class Scene{
public:
	Scene(); //constructor
	
	virtual bool init();
	virtual bool run();
	virtual void cleanup();
	~Scene(); //deconstructor

protected:
	bool initCompleted;
	SceneState thisSceneState;
};




#endif