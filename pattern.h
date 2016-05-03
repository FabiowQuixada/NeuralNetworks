#ifndef PATTERN_H
#define PATTERN_H

#include <iostream>
#include <vector>

#include "vector.h"

typedef std::vector<int> IntList;

class Pattern
{
	public:
		Pattern();
		Pattern(const char*);
       ~Pattern();

        void populate(IntList);

		int size() const;
		int input(int) const;
		int width() const;
		int height() const;
		Vector toVector() const;

		bool set_dimensions(int,int);
		void completePrint();
		void print();

	private:
        int *inputList;
        int _width, _height;
        int _size;

        void load(const char *fileName);

		friend std::ostream &operator<<(std::ostream&, const Pattern);
};

#endif // PATTERN_H
