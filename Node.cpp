#include "Node.h"

Node::Node(const int value, const Node* next)
    : m_value(value), m_next(next)
{
}

int  Node::value() const { return m_value; }
int& Node::valueRef() { return m_value; }
void Node::setValue(const int v) { m_value = v; }
Node* Node::next() const { return m_next; }
void  Node::setNext(const Node* n) { m_next = n; }
