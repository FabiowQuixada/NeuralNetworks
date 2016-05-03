#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"
#include <list>

class Graph
{
	public:
		Graph();
       ~Graph();
       int id() const;
       Node* source() const;

       void set_id();
       void load(const char *file);
       void add_node(Node*);

       bool is_oriented() const;

       void draw() const;

	protected:
        int ID;
        static int graphID;
        Node *source_;
        std::list<Node*> nodeList;

        bool oriented;

        friend std::ostream &operator<<(std::ostream&, const Graph);
};

#endif // GRAPH_H

