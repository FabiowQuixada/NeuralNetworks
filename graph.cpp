#include "graph.h"

#include <iostream>

int Graph::graphID = 0;

Graph::Graph()
{
    ID = -1;
    oriented = false;
}

Graph::~Graph()
{

}

void Graph::load(const char *file)
{
	std::ifstream stm;
	std::list<Node*>::iterator it, it2;
	int input, edges, a;

	stm.open(file);

	if(stm.is_open())
	{
        std::list<Point*> pointList;

        stm >> input; // Number of nodes in the graph;

        // Creates that number of nodes;
        for(int i = 0; i < input; ++i)
        {
            Node *n = new Node();
            n->set_id();
            nodeList.push_back(n);
        }

        // For each of them, add the proper edges;
        for(int i = 0; i < input; ++i)
        {
            stm >> edges; // Number of points in that closure;

            for(int e = 0; e < edges; ++e)
            {
                stm >> a;

                for(it = nodeList.begin(); it != nodeList.end(); ++it)
                    if((*it)->id()==i) break;

                for(it2 = nodeList.begin(); it2 != nodeList.end(); ++it2)
                    if((*it2)->id()==a) break;

                Edge *e = new Edge(*it,*it2);
                e->set_id();

                (*it)->add_edge(e);
            }

        }

		stm.close();
	}
}

int Graph::id() const {return ID;}

void Graph::set_id() {ID = graphID++;}
void Graph::add_node(Node *n) {nodeList.push_back(n);}

bool Graph::is_oriented() const {return oriented;}

void Graph::draw() const
{
    std::list<Node*>::const_iterator it;

	for(it = nodeList.begin(); it != nodeList.end(); ++it)
        (*it)->draw_edges();

	for(it = nodeList.begin(); it != nodeList.end(); ++it)
        (*it)->draw();
}

std::ostream &operator<<(std::ostream &output, const Graph g)
{
	std::list<Node*>::const_iterator it;

	std::cout << "Grafo " << g.id() << std::endl;

	std::cout << "  Lista de nos:" << std::endl;

	for(it = g.nodeList.begin(); it != g.nodeList.end(); ++it)
        std::cout << "     " << **it;

	return output;
}
