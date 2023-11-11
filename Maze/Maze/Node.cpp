#include "Node.h"

Node::Node()
{
	/*empty*/
}

Node::Node(int value, int type, std::pair<int,int> coord) :m_value(value), m_type(type),m_coord(coord)
{
	/*empty*/
}

void Node::setValue(int value)
{
	m_value = value;
}

void Node::setType(int type)
{
	m_type = type;
}

void Node::setCoord(std::pair<int, int> coord)
{
	m_coord = coord;
}

void Node::AddNeighbor(Node* node)
{
	neighbors.push_back(node);
}

int Node::getType()
{
	return m_type;
}

std::pair<int, int> Node::getCoord()
{
	return m_coord;
}

int Node::getValue()
{
	return m_value;
}

std::list<Node*> Node::getNeighbors()
{
	return neighbors;
}

bool Node::operator==(const Node& other) const
{
	return m_value == other.m_value;
}

