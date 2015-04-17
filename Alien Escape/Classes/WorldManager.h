/*
WorldManager.h

WorldManager is a singleton class used to access all game information from anywhere in the 
system. It also manages collisions between objects in the game by checking the game 
objects bounding boxes. The WorldManager communicates directly with the games Data Access object
allowing data to be read from, and written to XML files stored on the device. All aspects of the game can
be modified by the World Manager. 

@author	David Morton K00179391
@date	13.4.15
*/
#ifndef WORLDMANAGER_H_
#define WORLDMANAGER_H_

//Includes
#include <vector>
#include "Player.h"
#include "Subject.h"
#include "DAO\GameDAO.h"

//Forward Declarations
class IGameDAO;
class Scene;
class Node;
class Achievements;

class WorldManager : public Subject
{
public:
	//Return World Manager instance
	static WorldManager* getInstance();

	//Initialize the World Manager
	bool init();

	/*
		Transfer control to scene and start its update loop.

		@param Scene* scene pointer to a game scene
	*/
	void runWithScene(Scene* scene);

	//Clean up all resources created by the World Manager
	void cleanUp();

	//Flip the in game gravity direction
	void flipGravity();

	//Reset the game world configuration
	void resetGame();

	/*
		Check if the XML configuration file exits

		@return bool true if the XML file exists
	*/
	bool isXMLFileExist();

	/*
		Create a default XML file if one does not exist

		@param IGameDAO
	*/
	void loadDefaultConfig(IGameDAO* dao);

	//Increase the game world speed
	void increaseGameWorldSpeed(){ m_nGameWorldSpeed += SPEED_INC; };

	//Register the player with the World Manager
	void registerPlayer(Player* player){ m_pPlayer = player; };
		
	//Register game nodes for collision detection
	void registerGameNode(Node* node){ m_vpGameNodes.push_back(node); }

	//Check collisions
	bool checkCollisions();

	//Read the games XML file
	std::string WorldManager::readDAO(std::string name);

	//Getters	
	SDL_Renderer* getRenderer(){ return m_Renderer; }; //Return the SDL Renderer
	int getGravityDirection(){ return m_eGravitationalPull; } // Gravity
	SDL_RendererFlip getRendererFlip(){ return m_RendererFlip; }; // Gravity direction
	float getGameWorldSpeed(){ return m_nGameWorldSpeed; };	// Game world speed
	Scene* getRunningScene(){ return currentRunningScene; }; // Current running scene
	Player* getPlayer(){ return m_pPlayer; }; // Player 
	float getAverageFPS(){ return m_fAverageFPS; }; // Frames Per second
	IGameDAO* getGameDAO(){ return m_pGameDAO; }; // Data Access Object

	//Setters
	void setGameWorldSpeed(float speed){ m_nGameWorldSpeed = speed; };		
	void setAverageFPS(float fps){ m_fAverageFPS = fps; }; 
private:
	//Private singleton ctor and dtor
	WorldManager();
	~WorldManager();

	//Static reference for system wide access
	static WorldManager* m_Instance; 
		
	//SDL window and renderer
	SDL_Window* m_Window = NULL;
	SDL_Renderer* m_Renderer = NULL;

	//Game world data
	Gravity m_eGravitationalPull; // Gravity direction
	SDL_RendererFlip m_RendererFlip;
	float m_nGameWorldSpeed;
	Scene* currentRunningScene;
	bool m_bIsPaused;
	float m_fAverageFPS;
	Player* m_pPlayer;	
	std::vector<Node*> m_vpGameNodes; //Vector do game nodes

	//Achievements
	Observer* m_pAchievementSystem;

	//DAO
	IGameDAO* m_pGameDAO = nullptr;	
	// reminder: release resources in cleanup
};
#endif