#ifndef HALFEDGE_H
#define HALFEDGE_H

#include <ostream>

#include "neuron.h"

class Neural_HalfEdge
{
	public:
		Neural_HalfEdge(Neuron *tail, Neuron *head);
       ~Neural_HalfEdge();
        int id() const;
		float  x() const;
		float  y() const;
		float  weight() const;
		float  length() const;
		Neuron* head() const;
		Neuron* tail() const;

		void set_id();
		void set_head(float,float);
		void set_tail(float,float);
		void set_weight(float);
		void addTo_weight(float);
		void set_color(float,float,float);
		void normalize();
		void invert();
		void move(float,float);

		Neural_HalfEdge operator-(Neural_HalfEdge);

		bool is_normalized() const;
        void draw() const;

	private:
		int ID;
		static int halfedgeID;
		static bool standard_size;
		float _weight;
		float r,g,b;
		bool normal;
		Neuron *_head, *_tail;

		void goToOrigin();

		friend std::ostream &operator<<(std::ostream&,Neural_HalfEdge);
};

#endif // N_HALFEDGE_H
