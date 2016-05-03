#ifndef POINT_H
#define POINT_H

#include <fstream>
#include <list>

class Point
{
	public:
		Point(float X=0.0, float Y = 0.0);
		int id() const;
		float x() const;
		float y() const;
		void set_pos(float,float);
		void add(float,float);

		void set_color(float,float,float);
		void draw() const;

		Point& operator=(const Point&);
		bool operator==(const Point&) const;
		bool operator!=(const Point&) const;

		class Vector operator-(const Point&);

	private:
		int id_;
		static int points_id;
		float _x,_y;
		float size;
		float r,g,b;
		float dist;
		std::list<Point*> points;

		friend std::ostream &operator<<(std::ostream&, const Point);
};

#endif
