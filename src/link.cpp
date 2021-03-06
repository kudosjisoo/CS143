#include "../include/link.hpp"
#include "../include/node.hpp"
#include "../include/packet.hpp"
#include "../include/eventqueue.hpp"

#include <cassert>
#include <algorithm>

int Link::pushPacket(Packet* packet){
	if(max_buf_size_in_byte > cur_buf_size_in_byte + packet->packet_size){
		double stime, etime;
		if (link_buffers.size() == 0)
		{
			stime = link_delay + EventQueue::cur_time;
		}
		else
		{
			LinkBuffer buffer = link_buffers.back();
			stime = std::max(buffer.end_time, EventQueue::cur_time + link_delay);	
		}

		etime = stime + (packet->packet_size) * (BITS_PER_BYTE) / link_rate;
		LinkBuffer buffer(packet->packet_size, stime, etime);

#ifdef JISOO
		buffer.packet = packet;
		for (int i = 0; i < link_buffers.size(); i++)
		{
			assert(buffer.start_time >= link_buffers[i].end_time);
		}
#endif
		link_buffers.push_back(buffer);
		cur_buf_size_in_byte += packet->packet_size;
		return 1;
	}
	else{
		num_packet_drop++;
		return -1;
	}
}

void Link::popPacket(Packet* packet){

	packet_thru += packet->packet_size;
	cur_buf_size_in_byte -= packet->packet_size;

#ifdef JISOO
	LinkBuffer linkbuffer = link_buffers.front();
	assert(linkbuffer.packet == packet); //DO NOT ERASE THIS LINE.
#endif
	link_buffers.erase(link_buffers.begin());
}

double Link::getNumBytesOnLink()
{
	double bytes_on_link = 0;

	for (int i = 0; i < link_buffers.size(); i++)
	{
		if (EventQueue::cur_time < link_buffers[i].start_time)
		{
			bytes_on_link += link_buffers[i].size;
		}
		else if (EventQueue::cur_time < link_buffers[i].end_time)
		{
			double numerator = link_buffers[i].end_time - EventQueue::cur_time;
			double denominator = link_buffers[i].end_time - link_buffers[i].start_time;
			double fraction = numerator / denominator;
			bytes_on_link += link_buffers[i].size * fraction;
		}
	}

	return bytes_on_link;
}

double Link::getNumBytesThruLink()
{
	double bytes_thru_link = 0;

	for (int i = 0; i < link_buffers.size(); i++)
	{
		if (EventQueue::cur_time > link_buffers[i].end_time)
		{
			bytes_thru_link += link_buffers[i].size;
		}
		else if (EventQueue::cur_time > link_buffers[i].start_time)
		{
			double numerator = EventQueue::cur_time - link_buffers[i].start_time;
			double denominator = link_buffers[i].end_time - link_buffers[i].start_time;
			double fraction = numerator / denominator;
			bytes_thru_link += link_buffers[i].size * fraction;
		}
	}
	
	bytes_thru_link += packet_thru;
	packet_thru = 0;
	return bytes_thru_link;
}

int Link::establishLink(Node* pointA, Node* pointB)
{
	A = pointA;
	B = pointB;
	return 1;
}

double Link::getDelay()
{
	if (link_buffers.size() == 0)
	{
		return link_delay;
	}
	else
	{
		return link_buffers.back().end_time - EventQueue::cur_time;
	}
}

Node* Link::get_other_node(Node* node)
{
	return (Node *)((uintptr_t)A ^ (uintptr_t)B ^ (uintptr_t)node);
}

