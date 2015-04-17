#ifndef ACHIEVEMENTS_H
#define ACHIEVEMENTS_H
/*
Achievements.h

Game achievements system

@author	David Morton K00179391 
@date	17.4.15
*/
#include <iostream>
#include "Observer.h"

enum Achivement {
	ACHIEVEMENT_RUN_10_METERS = 10,
	ACHIEVEMENT_RUN_20_METERS = 20,
	ACHIEVEMENT_RUN_30_METERS = 30
};

class Achievements : public Observer
{
public:			
	virtual ~Achievements(){}
	virtual void onNotify(Node* entity, Event event)
	{
		// Unlock achievement based on the event
		switch (event)
		{
		case EVENT_ENTITY_100:
			if (entity->getNodeType() == NODE_PLAYER)
			{
				unlock(ACHIEVEMENT_RUN_10_METERS);
			}
			break;
		case EVENT_ENTITY_200:
			if (entity->getNodeType() == NODE_PLAYER)
			{
				unlock(ACHIEVEMENT_RUN_20_METERS);
			}
			break;
		case EVENT_ENTITY_300:
			if (entity->getNodeType() == NODE_PLAYER)
			{
				unlock(ACHIEVEMENT_RUN_30_METERS);
			}
			break;			
		}
	}

private:
	void unlock(Achivement achievement)
	{		
		// Player distance achievements
		if (achievement == ACHIEVEMENT_RUN_10_METERS && !distance10AchievementUnlocked)
		{
			printf("Achievement Unlocked! Player has run %d meters!\n", achievement);
			distance10AchievementUnlocked = true;	
			// Create a new achievement unlocked event
		}		
		if (achievement == ACHIEVEMENT_RUN_20_METERS && !distance20AchievementUnlocked)
		{
			printf("Achievement Unlocked! Player has run %d meters!\n", achievement);
			distance20AchievementUnlocked = true;
		}
		if (achievement == ACHIEVEMENT_RUN_30_METERS && !distance30AchievementUnlocked)
		{
			printf("Achievement Unlocked! Player has run %d meters!\n", achievement);
			distance30AchievementUnlocked = true;
		}

		// Other player achievements
	}

	// Achievement records
	bool distance10AchievementUnlocked = false;
	bool distance20AchievementUnlocked = false;
	bool distance30AchievementUnlocked = false;
};

#endif