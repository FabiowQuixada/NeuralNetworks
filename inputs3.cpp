#include <fstream>
#include <iostream>
#include <vector>

#include "pattern.h"

Pattern input1()
{
    Pattern p;
    IntList aux;

    aux.push_back( 1);
    aux.push_back(-1);
    aux.push_back(-1);
    aux.push_back(-1);

    p.populate(aux);

    return p;
}

Pattern input2()
{
    Pattern p;
    IntList aux;

    aux.push_back( 1);
    aux.push_back( 1);
    aux.push_back(-1);
    aux.push_back(-1);

    p.populate(aux);

    return p;
}

Pattern input3()
{
    Pattern p;
    IntList aux;

    aux.push_back(-1);
    aux.push_back(-1);
    aux.push_back(-1);
    aux.push_back( 1);

    p.populate(aux);

    return p;
}

Pattern input4()
{
    Pattern p;
    IntList aux;

    aux.push_back(-1);
    aux.push_back(-1);
    aux.push_back( 1);
    aux.push_back( 1);

    p.populate(aux);

    return p;
}

IntList output1()
{
    IntList targetList;
    targetList.push_back( 1);
    targetList.push_back(-1);
    return targetList;
}

IntList output2()
{
    IntList targetList;
    targetList.push_back( 1);
    targetList.push_back(-1);
    return targetList;
}

IntList output3()
{
    IntList targetList;
    targetList.push_back(-1);
    targetList.push_back( 1);
    return targetList;
}

IntList output4()
{
    IntList targetList;
    targetList.push_back(-1);
    targetList.push_back( 1);
    return targetList;
}


