#include "vector.h"

#include <cmath>
#include <iostream>

#include "GL/glut.h"

float rad(float);
float degree(float);

bool Vector::standard_size = true;
int  Vector::drawing_size = 50;

Vector::Vector(Point p)
{
	setup();
	head = p;
	head.set_color(1,0.3,0.3);
}

Vector::Vector(Point t, Point h)
{
    setup();

    head = h;
    tail = t;
}

Vector::Vector(int d)
{
    setup();
    set_dimension(d);
}

void Vector::setup()
{
    r = 1;
	g = 1;
	b = 1;
	_dimension = -1;
	vector = NULL;
	head = NULL;
	tail = NULL;
}

float Vector::x() const {return head.x();}
float Vector::y() const {return head.y();}
float Vector::x_length() const {return head.x()-tail.x();}
float Vector::y_length() const {return head.y()-tail.y();}
float Vector::x_absLength() const {return abs(head.x()-tail.x());}
float Vector::y_absLength() const {return abs(head.y()-tail.y());}
float Vector::angle() const // In degrees;
{
    float a = degree(acos(x_length()/length()));
    bool q3or4 = false;

    std::cout << a << std::endl;

    if(a==360) return 0.0;

    if(y_length()<0) q3or4 = true;


    if(!q3or4)
        return a;
    else
        return 360-a;

}

void Vector::set(Point p)      {head.set_pos(p.x(), p.y());}
void Vector::set(float a, float b)      {head.set_pos(a,b);}
void Vector::set_tail(Point p) {tail.set_pos(p.x(), p.y());}
void Vector::set_tail(float a, float b) {tail.set_pos(a,b);}
void Vector::set_color(float R, float G, float B) {r = R; g = G; b = B;}

void Vector::normalize()
{
    head.set_pos(x_length()/length() + tail.x(),
                 y_length()/length() + tail.y());
}

void Vector::rotate(float a)
{
    head = Point(tail.x() + drawing_size*cos(rad(a+angle())),
                 tail.y() + drawing_size*sin(rad(a+angle())));
}

/// Cross-product;
Vector Vector::operator^(const Vector& v)
{
	Vector result;

    Point p(
		0,//this->y() * v.z()  -  this->z() * v.y(),
		0//this->z() * v.x()  -  this->x() * v.z()
	);

    result.set(p);
    result.set_tail(this->tail);

    return result;
}

/// Dot-product;
Vector Vector::operator|(const Vector& v)
{
	Vector result;

    Point p(
		this->x() * v.x(),
		this->y() * v.y()
    );

    result.set(p);
    result.set_tail(this->tail);

    return result;
}

int Vector::dimension() const {return _dimension;}
float Vector::value(int i) const {return vector[i];}

Vector Vector::operator-(const Vector& v)
{
	if(dimension() != v.dimension())
	{
        std::cout << "Erro";
	}

	Vector result(dimension());

	for(int i = 0; i < dimension(); ++i)
        result.set_value(i, this->value(i) - v.value(i));

    return result;
}

float Vector::length() const
{
	float x = x_length();
	float y = y_length();

	return sqrt(x*x + y*y);
}

float Vector::length2() const
{
	float sum = 0.0;

	for(int i = 0; i < _dimension; ++i)
        sum += vector[i]*vector[i];

	return sqrt(sum);
}

void Vector::set_dimension(int d)
{
    vector = new float[d];
    _dimension = d;
}

void Vector::set_value(int d, float value)
{
    if(vector == NULL)
    {

    } else if(d < 0 or d > _dimension)
    {
        std::cout << "Erro!" << _dimension;
    }
    else
        vector[d] = value;
}

void Vector::draw() const
{
	#define ARROW_HEIGHT 10
	#define ARROW_WIDTH   7

//	glColor3f(r,g,b);
//
//	float x2 = x_length();
//	float y2 = y_length();
//	float angle = rad(this->angle());
//
//	// If all vector should be drawn in a representative
//	// way, ie, if they should have the same aparent length
//	// (but keeping their true length)...
//	if(standard_size)
//	{
//		// ...a constant scale factor is multiplied
//		// by the corresponding unit-vector;
//		x2 = drawing_size*(x_length()/length());
//		y2 = drawing_size*(y_length()/length());
//	}
//
//	// The "body" of the vector;
//	glBegin(GL_LINES);
//		glVertex2f(tail.x(),tail.y());
//		glVertex2f(tail.x()+x2,tail.y()+y2);
//	glEnd();
//
//	// The "head" of the vector;
//	glBegin(GL_POLYGON);
//		glVertex2f(tail.x()+x2, tail.y()+y2);
//		glVertex2f(
//			tail.x()+x2-ARROW_HEIGHT*cos(angle) + ARROW_WIDTH*cos(rad(270)+angle),
//			tail.y()+y2-ARROW_HEIGHT*sin(angle) + ARROW_WIDTH*sin(rad(270)+angle)
//		);
//		glVertex2f(
//			tail.x()+x2-ARROW_HEIGHT*cos(angle) + ARROW_WIDTH*cos(rad(90)+angle),
//			tail.y()+y2-ARROW_HEIGHT*sin(angle) + ARROW_WIDTH*sin(rad(90)+angle)
//		);
//	glEnd();
}

std::ostream &operator<<(std::ostream &stream, Vector v)
{
	std::cout << std::endl << v.head
			  << std::endl << v.tail;

	return stream;
}

int Vector::quadrant() const
{
    float angle = this->angle();

         if(angle >=   0 and angle <  90) return 1;
    else if(angle >=  90 and angle < 180) return 2;
    else if(angle >= 180 and angle < 270) return 3;
    else if(angle >= 270 and angle < 360) return 4;
    else std::cout << "Vector::quadrant() - Angulo: " << angle << std::endl;

    return -1;
}
