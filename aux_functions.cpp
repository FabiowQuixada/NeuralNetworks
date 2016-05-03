#include <cmath>
#include <iostream>

#include "main_functions.h"

float rad(float d) {return d*3.141592653589793238/180.0;}

float degree(float r) {return r*(180.0/3.141592653589793238);}

void wait()
{
    int k; std::cin >> k;
}

float minusa(Pattern p, FloatList list)
{
    float sum = 0.0;

    for(int i = 0; i < p.size(); ++i)
    {
        float yey = p.input(i) - list[i];

        yey *= yey;

        sum += yey;
    }

    return sqrt(sum);
}
