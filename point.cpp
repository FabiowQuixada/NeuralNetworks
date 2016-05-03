#include "point.h"

#include <cmath>
#include <iostream>

#include "GL/glut.h"
#include "vector.h"

float rad(float);

int Point::points_id = 0;

Point::Point(float a, float b)
{
	_x = a;
	_y = b;
	dist = sqrt(_x*_x + _y*_y);
	size = 5.0;
	r = 1.0;
	g = 1.0;
	b = 0.0;
	id_ = points_id++;
}

int   Point::id() const {return id_;}
float Point::x() const   {return _x;}
float Point::y() const   {return _y;}

void Point::set_pos(float a, float b) {_x = a; _y = b;}
void Point::add(float a, float b) {_x += a; _y += b;}
void Point::set_color(float R, float G, float B) {r = R; g = G; b = B;}

void Point::draw() const
{
	// Draws the interior;
//	glColor3f(r,g,b);
//	glBegin(GL_POLYGON);
//		for(int i = 0; i < 360; ++i)
//			glVertex2f(cos(rad(i))*size+_x, sin(rad(i))*size+_y);
//	glEnd();
//
//	// Draws the border;
//	glColor3f(0.0f,0.0f,0.0f);
//	glBegin(GL_LINE_LOOP);
//		for(int i = 0; i < 360; ++i)
//			glVertex2f(cos(rad(i))*size+_x, sin(rad(i))*size+_y);
//	glEnd();
}

Point& Point::operator=(const Point &p)
{
	_x = p.x();
	_y = p.y();

	return *this;
}

bool Point::operator==(const Point &p) const
{
	#define tolerance 0.05

	if(abs(x()-p.x()) < tolerance and abs(y()-p.y()) < tolerance)
        return true;

	return false;
}

bool Point::operator!=(const Point &p) const {return !(*this==p);}

Vector Point::operator-(const Point &p) {return Vector(*this, p);}

std::ostream &operator<<(std::ostream &output, const Point p)
{
	std::cout << "Ponto P" << p.id()
			  << " (" << p.x() << ", " << p.y() << ")";

	return output;
}
