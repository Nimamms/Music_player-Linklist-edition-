#ifndef NODE_H
#define NODE_H
#include "music.h"


class Node
{
public :
    Music Data ;
    Node * next ;
    Node * prev ;

    Node(Music x) : Data(x) , next(nullptr) , prev(nullptr) {}
};



#endif // NODE_H
