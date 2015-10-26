#ifndef NETWORK_H
#define NETWORK_H

#include <map>

#include "eventqueue.hpp"

class Flow;
class FlowInfo;
class Host;
class Link;
class LinkInfo;
class Router;

class Network {
public:
	Network(){}

	int registerFlow(char* id, FlowInfo&);
	int registerHost(char* id);
	int registerLink(char* id, LinkInfo&);
	int registerRouter(char* id);

	int connectLink(char* link_id, char* node1_id, char* node2_id);
	
	Flow* getFlow(char* id) { return m_flows[*id];}
	Host* getHost(char* id) { return m_hosts[*id];}
	Link* getLink(char* id) { return m_links[*id];}
	Router* getRouter(char* id){ return m_routers[*id];}

private:
	std::map<char, Flow*> m_flows;
	std::map<char, Host*> m_hosts;
	std::map<char, Link*> m_links;
	std::map<char, Router*> m_routers;
};

#endif //NETWORK_H