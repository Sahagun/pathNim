#ifndef CIRCULARDOUBLYLINKEDLIST_H
#define CIRCULARDOUBLYLINKEDLIST_H

#pragma once
struct DoublyLinkedNode {
    DoublyLinkedNode *next, *previous;
    int value;
};

class CircularDoublyLinkedList {
    int size;
    DoublyLinkedNode* head;
    DoublyLinkedNode* CreateNode(int value);
public:
    CircularDoublyLinkedList();
    DoublyLinkedNode* getHead();
    DoublyLinkedNode* getTail();
    int length();

    void setHead(DoublyLinkedNode*);
    void reverse(void);

    void InsertAtHead(int value);
    void InsertAtTail(int value);
    void InsertAtIndex(int index, int value);

    DoublyLinkedNode* GetNodeAtIndex(int index);
    void RemoveNodeAtIndex(int index);
};

#endif // CIRCULARDOUBLYLINKEDLIST_H
