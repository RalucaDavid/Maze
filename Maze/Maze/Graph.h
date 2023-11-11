#pragma once
#include "Arch.h"
#include <fstream>
#include <utility>
#include <queue>
#include <functional>

class Graph
{
private:
	std::vector<Node*> m_nodes;
	std::vector<Arch*> m_arches;
public:
	Graph();
	void AddNode(int value,int type,std::pair<int,int>coord);
	void AddArch(Node* source, Node* destination);
	void CreateGraph();
	void BFS();
	std::vector<Node*> getNodes();
	std::vector<Arch*> getArches();
	~Graph();
};

