#include "halfedge.h"

#include <cmath>
#include <iostream>

#include "GL/glut.h"

float rad(float);
float degree(float);

int Neural_HalfEdge::halfedgeID = 0;
bool Neural_HalfEdge::standard_size = true;

Neural_HalfEdge::Neural_HalfEdge(Neuron *t, Neuron *h)
{
	ID = -1;
	_head = h;
	_tail = t;
	_weight = 0.0;
	normal = false;
	r = 1.0;
	g = 1.0;
	b = 0.0;

	t->add_outgoingEdge(this);
	h->add_incomingEdge(this);
}

Neural_HalfEdge::~Neural_HalfEdge() {}

int     Neural_HalfEdge::id() const {return ID;}
Neuron* Neural_HalfEdge::head() const {return _head;}
Neuron* Neural_HalfEdge::tail() const {return _tail;}
float   Neural_HalfEdge::weight() const {return _weight;}

void Neural_HalfEdge::set_id() {ID = halfedgeID++;}
void Neural_HalfEdge::set_weight(float w) {_weight = w;}
void Neural_HalfEdge::addTo_weight(float w) {_weight = _weight + w;}
void Neural_HalfEdge::set_color(float R, float G, float B) {r = R; g = G; b = B;}

void Neural_HalfEdge::invert()
{
    Neuron *aux = _head;
    _head = _tail;
    _tail = aux;
}

void Neural_HalfEdge::draw() const
{
	/*#define ARROW_HEIGHT  5
	#define ARROW_WIDTH  10
	#define STD_SIZE     25

	float x_length = head()->x()-tail()->x();
	float y_length = head()->y()-tail()->y();

	float xPrime = (ARROW_HEIGHT/length())*x_length;
	float yPrime = (ARROW_HEIGHT/length())*y_length;

	glColor3f(r,g,b);

	// If all half-edges should be drawn in a representative
	// way, ie, if they should have the same aparent length
	// (but keeping their true length)...
	if(standard_size)
	{
		// ...a constant scale factor is multiplied
		// by the corresponding unit-half-edge;
		x_length = STD_SIZE*(x_length/length());
		y_length = STD_SIZE*(y_length/length());
	}

	// The "body" of the half-edge;
	glBegin(GL_LINES);
		glVertex2f(tail()->x(), tail()->y());
		glVertex2f(tail()->x()+x_length, tail()->y()+y_length);
	glEnd();

	// The "head" of the half-edge;
    glBegin(GL_POLYGON);
        glVertex2f(tail()->x()+x_length, tail()->y()+y_length);
        glVertex2f(
            -y_length/ARROW_WIDTH +tail()->x()+x_length-xPrime,
             x_length/ARROW_WIDTH +tail()->y()+y_length-yPrime
        );
        glVertex2f(
             y_length/ARROW_WIDTH +tail()->x()+x_length-xPrime,
            -x_length/ARROW_WIDTH +tail()->y()+y_length-yPrime
        );
    glEnd();
    */
}

std::ostream &operator<<(std::ostream &stream, Neural_HalfEdge v)
{
	std::cout << "Aresta " << v.id() << std::endl;
	std::cout << " - Peso: " << v.weight() << std::endl;
	std::cout << " - Origem: " << v.tail()->id() << std::endl;
	std::cout << " - Destino: " << v.head()->id() << std::endl;

	return stream;
}
