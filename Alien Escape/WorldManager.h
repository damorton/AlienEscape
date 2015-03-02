#ifndef WORLDMANAGER_H_
#define WORLDMANAGER_H_

#include <vector>
#include <memory>

// forward declarations
class Player;
class Enemy;
class IEnemyFactory;
 
class WorldManager
{

public:
	virtual bool init();	// initialization
	static WorldManager* getInstance(); // WorldManager instance
	
	// getters
	std::shared_ptr<Player> getPlayer(){ return m_pPlayer; }; // player
	std::vector<std::shared_ptr<Enemy>> getEnemyVector(){ return m_pvEnemies; }; // vector of enemies
	std::shared_ptr<Boss> getBoss(){ return m_pBoss; };	// Boss
	std::shared_ptr<IEnemyFactory> getEnemyFactory(){ return m_pIEnemyFactory; }; // EnemyFactory Interface
		
	// setters
	std::shared_ptr<Player> createPlayer();	// create Player	
	std::shared_ptr<IEnemyFactory> WorldManager::createEnemyFactory(); // create EnemyFactory

	virtual void cleanUp(); // delete WorldManager and stored objects

private:
	static WorldManager* m_Instance; // WorldManager instance
	WorldManager(){ this->init(); }; // constructor 
	~WorldManager(){ this->cleanUp(); }; // deconstructor
		
	// store the Game World objects	
	std::shared_ptr<Player> m_pPlayer; // Player
	std::shared_ptr<Enemy> m_pEnemy1;
	std::shared_ptr<Enemy> m_pEnemy2;
	std::shared_ptr<Enemy> m_pEnemy3;
	std::shared_ptr<IEnemyFactory> m_pIEnemyFactory; // EnemyFactory
	std::vector<std::shared_ptr<Enemy>> m_pvEnemies; // Enemy vector
	std::shared_ptr<Boss> m_pBoss; // Boss	
};

#endif