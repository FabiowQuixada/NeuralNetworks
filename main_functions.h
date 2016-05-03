#ifndef MAIN_FUNCTIONS_H
#define MAIN_FUNCTIONS_H

#include "pattern.h"
#include "neuron.h"
#include "halfedge.h"

typedef std::vector<Pattern*> PatternList;
typedef std::vector<int> IntList;

typedef std::vector<Neuron*> NeuronList;
typedef std::vector<Neural_HalfEdge*> HalfEdgeList;

PatternList   BIPOLAR_INPUT();
IntList       AND();
IntList       OR();
IntList       XOR();
void          wait();
IntList       A();
IntList       B();
IntList       C();
IntList       D();
IntList       E();
IntList       J();
IntList       K();

Pattern input1();
Pattern input2();
Pattern input3();
Pattern input4();

IntList output1();
IntList output2();
IntList output3();
IntList output4();

float minusa(Pattern p, FloatList list);

#endif // MAIN_FUNCTIONS_H
