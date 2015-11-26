#include "../../include/event/rxackevent.hpp"
#include "../../include/networkmanager.hpp"
#include "../../include/flow.hpp"
#include "../../include/link.hpp"
#include "../../include/packet.hpp"
#include "../../include/node.hpp"
#include "../../include/common.hpp"

#include <iostream>

int RxAckEvent::handleEvent()
{
	rx_link->popPacket(rx_packet);
	rx_node->receivePacket(rx_packet);

#ifdef CHECK_DROP
	std::cout << "receive src event: " << rx_packet->packet_seq_id \
		<< std::endl;
#endif//DEBUG

	NetworkManager* nm = NetworkManager::getInstance();
	Flow* rx_flow = nm->getFlow(rx_packet->packet_flow_id);


#ifndef TESTCASE0
	Packet* ack_packet = rx_flow->genAckPacket(rx_packet);
	ack_packet->start_t = rx_packet->start_t;
#else
	Packet* ack_packet = new Packet(*rx_flow, rx_packet->packet_dest,\
		rx_packet->packet_src, ACK_PACKET);
	ack_packet->test = rx_packet->test;
#endif
	// And transmit back to sender

	delete rx_packet;
	return commonTransmit(rx_node, ack_packet);
}
