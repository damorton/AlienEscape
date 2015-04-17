#ifndef OBSERVER_H
#define OBSERVER_H
/*
	Observer.h

	Observer interface for design pattern implmentation

	@author	David Morton K00179391
	@date	17.4.15
*/
// Includes
#include "Definitions.h"

class Observer
{
public:		
	virtual ~Observer(){}

	/*
		Notify all observers of an event

		@param Node* pointer to a game node
		@param Event system wide event
	*/
	virtual void onNotify(Node* node, Event event) = 0;	
};

#endif
