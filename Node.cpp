#include "Node.h"

Node::Node(int value, Node* next)
    : m_value(value), m_next(next)
{
}

int  Node::value() const { return m_value; }
int& Node::valueRef() { return m_value; }
void Node::setValue(int v) { m_value = v; }
Node* Node::next() const { return m_next; }
void  Node::setNext(Node* n) { m_next = n; }
