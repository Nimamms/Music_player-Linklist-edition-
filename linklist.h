#ifndef LINKLIST_H
#define LINKLIST_H
#include "node.h"


class Linklist
{
public:
    Node * head ;

    Linklist() ;


    void pushback(Music music)
    {
        Node * new_node = new Node(music) ;
        if (head == nullptr)                     //if linklist was empty
            head = new_node ;
        else
        {
            Node* temp = head;
            while (temp->next != nullptr)
                temp = temp->next ;
            temp->next = new_node ;

        }
    }

    int get_lenght(Node* head) ;


};

#endif // LINKLIST_H
