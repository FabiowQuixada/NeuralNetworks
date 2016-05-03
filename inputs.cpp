#include <fstream>
#include <iostream>
#include <vector>

#include "pattern.h"

typedef std::vector<Pattern*> PatternList;
typedef std::vector<int> IntList;

PatternList BIPOLAR_INPUT()
{
    PatternList trainList;
    IntList aux;

    Pattern *t1 = new Pattern();
    Pattern *t2 = new Pattern();
    Pattern *t3 = new Pattern();
    Pattern *t4 = new Pattern();

    aux.push_back( 1); aux.push_back( 1); t1->populate(aux); aux.empty();
    aux.push_back( 1); aux.push_back(-1); t2->populate(aux); aux.empty();
    aux.push_back(-1); aux.push_back( 1); t3->populate(aux); aux.empty();
    aux.push_back(-1); aux.push_back(-1); t4->populate(aux); aux.empty();

//        Pattern *t1 = new Pattern(2); t1->add_input( 1); t1->add_input( 1);
//    Pattern *t2 = new Pattern(2); t2->add_input( 1); t2->add_input(-1);
//    Pattern *t3 = new Pattern(2); t3->add_input(-1); t3->add_input( 1);
//    Pattern *t4 = new Pattern(2); t4->add_input(-1); t4->add_input(-1);

    trainList.push_back(t1);
    trainList.push_back(t2);
    trainList.push_back(t3);
    trainList.push_back(t4);

    return trainList;
}

IntList AND()
{
    IntList targetList;

    targetList.push_back( 1);
    targetList.push_back(-1);
    targetList.push_back(-1);
    targetList.push_back(-1);

    return targetList;
}

IntList A()
{
    IntList aList;
    aList.push_back( 1);  aList.push_back(-1); aList.push_back(-1); aList.push_back(-1); aList.push_back(-1); aList.push_back(-1); aList.push_back(-1); // A;

    return aList;
}

IntList B()
{
    IntList bList;
    bList.push_back(-1);  bList.push_back( 1); bList.push_back(-1); bList.push_back(-1); bList.push_back(-1); bList.push_back(-1); bList.push_back(-1); // B;
    return bList;
}
IntList C()
{
    IntList cList;
    cList.push_back(-1);  cList.push_back(-1); cList.push_back( 1); cList.push_back(-1); cList.push_back(-1); cList.push_back(-1); cList.push_back(-1); // C;
    return cList;
}
IntList D()
{
    IntList dList;
    dList.push_back(-1);  dList.push_back(-1); dList.push_back(-1); dList.push_back( 1); dList.push_back(-1); dList.push_back(-1); dList.push_back(-1); // D;
    return dList;
}
IntList E()
{
    IntList eList;
    eList.push_back(-1);  eList.push_back(-1); eList.push_back(-1); eList.push_back(-1); eList.push_back( 1); eList.push_back(-1); eList.push_back(-1); // E;
    return eList;
}
IntList J()
{
    IntList jList;
    jList.push_back(-1);  jList.push_back(-1); jList.push_back(-1); jList.push_back(-1); jList.push_back(-1); jList.push_back( 1); jList.push_back(-1); // J;
    return jList;
}
IntList K()
{
    IntList kList;
    kList.push_back(-1);  kList.push_back(-1); kList.push_back(-1); kList.push_back(-1); kList.push_back(-1); kList.push_back(-1); kList.push_back( 1); // K;
    return kList;
}

IntList OR()
{
    IntList targetList;
    targetList.push_back( 1);
    targetList.push_back( 1);
    targetList.push_back( 1);
    targetList.push_back(-1);
    return targetList;
}

IntList XOR()
{
    IntList targetList;

    targetList.push_back(-1);
    targetList.push_back( 1);
    targetList.push_back( 1);
    targetList.push_back(-1);

    return targetList;
}
