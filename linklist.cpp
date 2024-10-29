#include "linklist.h"

Linklist::Linklist()
{
    head = nullptr ;
}


Linklist::get_lenght(Node * head)
{
    int len = 0 ;
    Node * cur = head ;
    while (cur != nullptr)
    {
        len++;
        cur = cur->next ;
    }
    return len ;
}
