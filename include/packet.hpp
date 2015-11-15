#ifndef PACKET_H
#define PACKET_H

#include <string>
#include <unordered_map>

const int BITS_PER_BYTE = 8;

// fixed packet size in byte
const int SRC_PACKET = 0;
const int ACK_PACKET = 1;
const int ROUT_PACKET = 2;

/* forward declaration class */
class Flow; 

// Assume that packet size are fix
class Packet {
	public:
		Packet(std::string flow_id, std::string src, std::string dest, int type, int size)\
		: packet_flow_id(flow_id),\
		  packet_src(src), \
		  packet_dest(dest), \
		  packet_type(type)
		{};

		std::string packet_flow_id;
		std::string packet_src;
		std::string packet_dest;
		int packet_type;
		int packet_size = SIZE_TABLE[packet_type];
		int id = -1;
};

const std::unordered_map<int, int> SIZE_TABLE({
	{SRC_PACKET, 1500},
	{ACK_PACKET, 40},
	{ROUT_PACKET, 40}
});


#endif //PACKET_H
