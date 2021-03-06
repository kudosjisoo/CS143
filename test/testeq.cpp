/**
  * Checks the functionality of the event queue.
  */

#ifndef _MSC_VER
#include "../include/eventqueue.hpp"
#include "../include/event.hpp"
#else
#include "eventqueue.hpp"
#include "event.hpp"
#endif

#include <cassert>
#include <cstdlib>

int main()
{
	EventQueue event = *EventQueue::getInstance();
	Event event1("H1"), event2("H2"), event3("H3"), event4("H4"), event5("H5");
	
	event1.time = 0.5;
	event2.time = 0.6;
	event3.time = 0.3;

	event.push(&event1); 
	event.push(&event2);
	event.push(&event3);
	
	//the order now should be 0.3/0.5/0.6
	assert(event.pop()->time == 0.3);

	event4.time = 1;
	event5.time = 0.1;

	event.push(&event4);
	event.push(&event5);

	//the order should now be 0.1/0.5/0.6/1
	assert(event.pop()->time == 0.1);
	assert(event.pop()->time == 0.5);
	assert(event.pop()->time == 0.6);
	assert(event.pop()->time == 1);

	//if nothing is in the event, return "-1"
	assert(event.pop()->time == -1); 
	assert(event.pop()->time == -1);

	printf("Test Success - event queue\n");

	return EXIT_SUCCESS;
}