#ifndef VECTOR_H
#define VECTOR_H

#include "point.h"

class Frame;

class Vector
{
	public:
		Vector(Point p = 0);
		Vector(Point t, Point h);
		Vector(int);

		int dimension() const;
		float x() const;
		float y() const;
		float x_length() const;
		float y_length() const;
		float length() const;
		float length2() const;
		float angle() const;  // In degrees;
		int quadrant() const; // With its tail viewed as the origin;
		void normalize();
		void rotate(float);
		void rotate();

        float value(int) const;

		bool is_normalized() const;

		void draw() const;
		void set(Point);
		void set(float,float);
		void set_tail(Point);
		void set_tail(float,float);
		void set_color(float,float,float);

		void set_dimension(int);
		void set_value(int, float);

		Vector operator^(const Vector&); // Cross-product;
		Vector operator|(const Vector&); // Dot-product;
		Vector operator-(const Vector&);

	private:
		Point head,
              tail;
		float r,g,b;

		float *vector;
		int _dimension;


		float x_absLength() const;
		float y_absLength() const;
		void setup();

		static bool standard_size;
		static int drawing_size;

		friend std::ostream &operator<<(std::ostream&,Vector);
};

#endif
