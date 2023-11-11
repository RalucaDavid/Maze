#pragma once
#include <vector>
#include <list>

class Node
{
private:
	int m_value;
	int m_type;
	std::pair<int, int> m_coord;
	std::list<Node*> neighbors;
public:
	Node();
	Node(int value,int type, std::pair<int,int> coord);
	void setValue(int value);
	void setType(int type);
	void setCoord(std::pair<int, int> coord);
	void AddNeighbor(Node* node);
	int getType();
	std::pair<int, int> getCoord();
	int getValue();
	std::list<Node*> getNeighbors();
	bool operator==(const Node& other) const;
};

