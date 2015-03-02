
#ifndef COLLISION_H_
#define	COLLISION_H_

// includes 
#include <vector>
#include <memory>

// forward declarations
class GameObject;
class Player;

/*	Singleton CollisionManager */
class CollisionManager
{
public:
	virtual bool init(); // initialization
	static CollisionManager* getInstance(); // instance of CollsionManager

	// register with the collision manager
	void registerWithCollisionManager(std::shared_ptr<GameObject> obj);

	// register the player object
	void registerPlayer(std::shared_ptr<Player> player);

	// check for collisions between the player and all other game objects
	bool checkCollisons();
	virtual void cleanUp(); // delete CollisionManager

	// getters 
	std::shared_ptr<Player> getPlayer(){ return m_pPlayer; }; // player
	std::vector<std::shared_ptr<GameObject>> getGameObjectVector(){ return m_pvGameObjects; }; // vector of enemies
	
private:
	static CollisionManager* m_Instance; 
	CollisionManager(){ this->init(); }; // constructor
	~CollisionManager(){ this->cleanUp(); }; // deconstructor
	
	std::vector<std::shared_ptr<GameObject>> m_pvGameObjects; // vector of GameObject pointers
	std::shared_ptr<Player> m_pPlayer; // player 
};

#endif