#include "Graph.h"

Graph::Graph()
{
	/*empty*/
}

void Graph::AddNode(int value,int type, std::pair<int, int>coord)
{
	Node* newNode = new Node(value,type,coord);
	m_nodes.push_back(newNode);
}

void Graph::AddArch(Node* source, Node* destination)
{
	Arch* newArch = new Arch(source, destination);
	m_arches.push_back(newArch);
    source->AddNeighbor(destination);
}

void ReadingMatrix(std::vector<std::vector<int>>& matrix, int& lines, int& columns)
{
    std::ifstream fin("Input.txt");
    fin >> lines >> columns;
    std::vector<int> column;
    int element;
    for (int index = 0; index < lines; index++)
    {
        for (int jndex = 0; jndex < columns; jndex++)
        {
            fin >> element;
            column.push_back(element);
        }
        matrix.push_back(column);
        column.clear();
    }
    fin.close();
}

void Graph::CreateGraph()
{
	std::vector<std::vector<int>> matrix;
	int lines;
	int columns;
	ReadingMatrix(matrix,lines,columns);
    int value = 1;
    for (int index = 0; index < lines; index++)
    {
        for (int jndex = 0; jndex < columns; jndex++)
        {
            if (matrix[index][jndex] != 0)
            {
                std::pair<int, int> coord = std::make_pair(index, jndex);
                AddNode(value, matrix[index][jndex], coord);
                value++;
            }
        }
    }
    int coord_lines[] = { 0,0,-1,1 };
    int coord_columns[] = { -1,1,0,0 };
    for (Node*& node : m_nodes)
    {
        for (int coord = 0; coord < 4; coord++)
        {
            int line = node->getCoord().first + coord_lines[coord];
            int column = node->getCoord().second + coord_columns[coord];
            for (Node*& node2 : m_nodes)
                if ((node2->getCoord().first == line) && (node2->getCoord().second == column))
                {
                    AddArch(node, node2);
                }
        }
    }
}

void Graph::BFS()
{
    Node* entry;
    for (Node*& node : m_nodes)
        if (node->getType() == 3)
        {
            entry = node;
            break;
        }
    std::vector<Node*>U; // unvisited nodes
    std::queue<Node*>V; // visited and unanalyzed nodes
    std::vector<Node*>W; // visited and analyzed nodes
    std::vector<int> p; // predecessors
    std::vector<int> l; // lengths
    std::vector<std::vector<int>> allPaths;
    V.push(entry);
    for (Node*& node : m_nodes)
      if(node->getValue()!=entry->getValue())
         U.push_back(node);
    for (int index = 1; index < m_nodes.size()+2; index++)
        p.push_back(0);
    for (int index = 1; index < m_nodes.size()+2; index++)
        l.push_back(0);
    while (!V.empty())
    {
        Node* x = V.front();
        std::list<Node*> neighbors = x->getNeighbors();
        for(Node*& y:neighbors)
        {
            if (std::find(U.begin(), U.end(), y) != U.end())
            {
                V.push(y);
                U.erase(std::find(U.begin(), U.end(), y));
                p[y->getValue()] = x->getValue();
                l[y->getValue()] = l[x->getValue()] + 1;
                if (y->getType() == 2)
                {
                    std::vector<int> currentPath;
                    int current = y->getValue();
                    while (current != entry->getValue())
                    {
                        currentPath.push_back(current);
                        current = p[current];
                    }
                    currentPath.push_back(entry->getValue());
                    allPaths.push_back(currentPath);
                }
            }
        }
        V.pop();
        W.push_back(x);
    }
    for (const std::vector<int>& path : allPaths)
    {
        for (int nodeValue : path)
        {
            for (Node*& node : m_nodes)
            {
                if (node->getValue() == nodeValue)
                {
                    if (node->getType() == 1)
                    {
                        node->setType(4);
                    }
                    break;
                }
            }
        }
    }
}

std::vector<Node*> Graph::getNodes()
{
	return m_nodes;
}

std::vector<Arch*> Graph::getArches()
{
	return m_arches;
}

Graph::~Graph()
{
    for (Node*& node : m_nodes) {
        delete node;
    }

    for (Arch*& arch : m_arches) {
        delete arch;
    }
}
