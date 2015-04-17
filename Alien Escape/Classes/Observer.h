#ifndef OBSERVER_H
#define OBSERVER_H
/*
	Observer interface for design pattern implmentation
*/
// Includes
#include "Definitions.h"

class Observer
{
public:		
	virtual ~Observer(){}
	virtual void onNotify(Node* node, Event event) = 0;	
};

#endif
