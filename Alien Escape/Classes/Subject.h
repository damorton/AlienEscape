#ifndef SUBJECT_H
#define SUBJECT_H

#define MAX_OBSERVERS 5

#include "Observer.h"

class Subject
{
private:
	Observer* m_AObservers[MAX_OBSERVERS];
	int m_iNumberOfObservers;
public:
	void notify(Node* entity, Event event)
	{
		for (int i = 0; i < m_iNumberOfObservers; i++)
		{
			m_AObservers[i]->onNotify(entity, event);
		}
	}

	void addObserver(Observer* observer)
	{
		// Add to array...
		m_AObservers[m_iNumberOfObservers] = observer;
		m_iNumberOfObservers++;
	}

	void removeObserver(Observer* observer)
	{
		// Remove from array...
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