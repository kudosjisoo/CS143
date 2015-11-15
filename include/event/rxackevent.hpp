#ifndef RXACKEVENT_H
#define RXACKEVENT_H

#include "rxevent.hpp"

class RxAckEvent : public RxEvent
{
public:
	RxAckEvent(Link* pLink, Node* pNode) : RxEvent(pLink, pNode) {}

	int handleEvent();
};

#endif


