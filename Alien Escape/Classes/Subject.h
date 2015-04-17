#ifndef SUBJECT_H
#define SUBJECT_H

#define MAX_OBSERVERS 5
/*
Subject.h

Subject contains an array of registered observers

@author	David Morton K00179391
@date	17.4.15
*/
//Includes
#include "Observer.h"

class Subject
{
private:
	// Array of registered observers
	Observer* m_AObservers[MAX_OBSERVERS];
	int m_iNumberOfObservers;
public:
	
	void notify(Node* entity, Event event)
	{
		// Walk the array and notify each observer
		for (int i = 0; i < m_iNumberOfObservers; i++)
		{
			m_AObservers[i]->onNotify(entity, event);
		}
	}

	// Register an observer
	void addObserver(Observer* observer)
	{		
		if (m_iNumberOfObservers <= MAX_OBSERVERS)
		{
			m_AObservers[m_iNumberOfObservers] = observer;
			m_iNumberOfObservers++;
			printf("Observer added : %d\n", m_iNumberOfObservers);
		}		
	}

	// Remove an observer
	void removeObserver(Observer* observer)
	{		
		for (int i = 0; i < m_iNumberOfObservers; i++)
		{
			if (m_AObservers[i] == observer)
			{
				m_AObservers[m_iNumberOfObservers] = nullptr;
				m_iNumberOfObservers--;
			}
		}		
	}

};

#endif