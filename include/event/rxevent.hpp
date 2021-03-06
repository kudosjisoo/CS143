#ifndef RXEVENT_H
#define RXEVENT_H

#include "../event.hpp"

/* Forward declaration */
class Link;
class Node;

/**
 * RxEvent implement Event class. This class is the common
 * interface class for RxACK, RxEND, RxRout event for
 * RxEventFactory
 */
class RxEvent : public Event
{
public:
	RxEvent(double t, Link* pLink, Node* pNode) :\
		rx_link(pLink), rx_node(pNode), Event(t)
	{}

	int handleEvent() { return 1; }

protected:
	Link* rx_link;
	Node* rx_node;
};

#endif //RXEVENT_H

