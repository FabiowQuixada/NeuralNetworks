#include "main_functions.h"

#include "networks/lvq.h"

void LVQa()
{
    LVQ net(4,2);

    Pattern *p1 = new Pattern(),
            *p2 = new Pattern(),
            *p3 = new Pattern(),
            *p4 = new Pattern(),
            *p5 = new Pattern();
    IntList aux1, aux2, aux3, aux4, aux5;
    PatternList list;

    aux1.push_back(1); aux1.push_back(1); aux1.push_back(0); aux1.push_back(0);
    aux2.push_back(0); aux2.push_back(0); aux2.push_back(0); aux2.push_back(1);
    aux3.push_back(0); aux3.push_back(0); aux3.push_back(1); aux3.push_back(1);
    aux4.push_back(1); aux4.push_back(0); aux4.push_back(0); aux4.push_back(0);
    aux5.push_back(0); aux5.push_back(1); aux5.push_back(1); aux5.push_back(0);

    p1->populate(aux1);
    p2->populate(aux2);
    p3->populate(aux3);
    p4->populate(aux4);
    p5->populate(aux5);

    list.push_back(p1);
    list.push_back(p2);
    list.push_back(p3);
    list.push_back(p4);
    list.push_back(p5);

    int k[6] = {0,1,1,0,1};

    net.train(list, k);

    std::cout << net;
}
