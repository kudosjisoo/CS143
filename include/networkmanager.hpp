#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <map>
#include <string>

class Flow;
class Node;
class Link;
class Router;

typedef std::map<std::string, Flow*> flow_t;
typedef std::map<std::string, Node*> node_t;
typedef std::map<std::string, Link*> link_t;


/**
 * Singleton class to create and retrieve network
 * structure
 */
class NetworkManager {
public:
	static NetworkManager* getInstance();

	int registerFlow(Flow&);
	int registerLink(Link&);
	int registerNode(Node&);

	void initNetworkSim(double log_interval, int complexity);
	int connectLink(std::string link_id, std::string node1_id, std::string node2_id);

	Flow* getFlow(std::string id);
	Node* getNode(std::string id);
	Link* getLink(std::string id);

	Flow* resetFlowIterator();
	Flow* getNextFlowIterator();
	Node* resetNodeIterator();
	Node* getNextNodeIterator();
	Link* resetLinkIterator();
	Link* getNextLinkIterator();
    
    Link* getLinkBtwNodes(std::string node1, std::string node2);

private:
	NetworkManager(){}
	static NetworkManager* manager;

	flow_t m_flows;
	node_t m_nodes;
	link_t m_links;

	flow_t::iterator m_flow_iter;
	node_t::iterator m_node_iter;
	link_t::iterator m_link_iter;
    
    std::map<std::string, std::string> node2link;
};

#endif //NETWORKMANAGER_H
