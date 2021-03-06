#ifndef EVENT_H
#define EVENT_H

/* C/C++ lib */
#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>


class Node;
class Packet;


/**
 * Base class for all types of event.
 */
class Event{
	public:
		Event(double t);

		/**
		 * commonTransmit puts packet on the link and
		 * generate corresponding receive event from RxEventFactory
		 * if necessary
		 */
		int commonTransmit(Node* node, Packet* pkt);

		// Abstract handler function
		virtual int handleEvent() { return 0; }
		double time = -1;



};

/*
 * Function used by "eventqueue" to order each events. We will
 * prioritize events that happens faster. This comparator will
 * be used by eventqueue to order events correctly.
 */
struct CompareEvent
{
	bool operator()(const Event* lhs, const Event* rhs) const
	{
		return lhs->time > rhs->time;
	}
};
#endif //EVENT_H

