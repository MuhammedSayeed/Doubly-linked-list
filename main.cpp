#include <iostream>
using namespace std;

class LinkedListNode
{
public:
    int data;
    LinkedListNode *next;
    LinkedListNode *back;
    LinkedListNode(int _data)
    {
        this->data = _data;
        this->next = NULL;
        this->back = NULL;
    }
};

class LinkedListIterator
{
private:
    LinkedListNode *currentNode;

public:
    LinkedListIterator()
    {
        currentNode = NULL;
    }
    LinkedListIterator(LinkedListNode *node)
    {
        currentNode = node;
    }
    int data()
    {
        return this->currentNode->data;
    }
    LinkedListIterator next()
    {
        this->currentNode = this->currentNode->next;
        return *this;
    }
    LinkedListNode *current()
    {
        return this->currentNode;
    }
};

class LinkedList
{
public:
    LinkedListNode *head = NULL;
    LinkedListNode *tail = NULL;
    LinkedListIterator begin()
    {
        LinkedListIterator itr(this->head); // static allocation
        return itr;
    }

    LinkedListNode *findNode(int _data)
    {
        for (LinkedListIterator itr = this->begin(); itr.current() != NULL; itr.next())
        {
            if (itr.data() == _data)
            {
                return itr.current();
            }
        }

        return NULL;
    }
    void insertLast(int _data)
    {
        LinkedListNode *newNode = new LinkedListNode(_data);
        if (this->tail == NULL)
        {
            this->head = newNode;
            this->tail = newNode;
        }
        else
        {
            newNode->back = this->tail;
            this->tail->next = newNode;
            this->tail = newNode;
        }
    }
    void insertAfter(int _nodeData, int _data)
    {
        LinkedListNode *newNode = new LinkedListNode(_data);
        LinkedListNode *node = this->findNode(_nodeData);
        newNode->next = node->next;
        newNode->back = node;
        node->next = newNode;
        if (newNode->next == NULL)
        {
            this->tail = newNode;
        }
        else
        {
            newNode->next->back = newNode;
        }
    }
    void insertBefore(int _nodeData, int _data)
    {
        LinkedListNode *newNode = new LinkedListNode(_data);
        LinkedListNode *node = this->findNode(_nodeData);
        newNode->next = node;

        if (node == this->head)
        {
            this->head = newNode;
        }
        else
        {
            newNode->back = node->back;
            node->back->next = newNode;
        }
        node->back = newNode;
    }
    void deleteNode(int _nodeData)
    {
        LinkedListNode *node = this->findNode(_nodeData);
        if (this->head == this->tail)
        {
            this->head = NULL;
            this->tail = NULL;
        }
        else if (node->back == NULL)
        {
            this->head = node->next;
            node->next->back = NULL;
        }
        else if (node->next == NULL)
        {
            this->tail = node->back;
            node->back->next = NULL;
        }
        else
        {
            node->back->next = node->next;
            node->next->back = node->back;
        }
        delete node;
    }
    void printList()
    {
        for (LinkedListIterator itr = this->begin(); itr.current() != NULL; itr.next())
        {
            cout << itr.data() << " -> ";
        }
        cout << "NULL";
        cout << endl;
    }
};

int main()
{

    LinkedList *list = new LinkedList();
    list->insertLast(1);
    list->insertLast(2);
    list->insertLast(3);
    list->insertLast(4);
    list->insertBefore(4, 22);
    list->printList();

    return 0;
}
