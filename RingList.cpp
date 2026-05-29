#include "RingList.h"

Node* RingList::nodeAt(const std::size_t index) const
{
    if (index >= m_size)
        throw std::out_of_range(
            "RingList: index " + std::to_string(index) +
            " is out of range (size = " + std::to_string(m_size) + ")");

    Node* cur = m_tail->next();
    for (std::size_t i = 0; i < index; ++i)
        cur = cur->next();
    return cur;
}

void RingList::copyFrom(const RingList& other)
{
    if (other.empty()) return;
    Node* cur = other.m_tail->next();
    for (std::size_t i = 0; i < other.m_size; ++i)
    {
        pushBack(cur->value());
        cur = cur->next();
    }
}

void RingList::moveFrom(RingList& other) noexcept
{
    m_tail = other.m_tail;
    m_size = other.m_size;
    other.m_tail = nullptr;
    other.m_size = 0;
}

RingList::RingList()
    : m_tail(nullptr), m_size(0)
{
}

RingList::RingList(const std::initializer_list<int> init) : RingList()
{
    for (int v : init)
        pushBack(v);
}

RingList::RingList(const RingList& other) : RingList()
{
    copyFrom(other);
}

RingList::RingList(RingList&& other) noexcept : RingList()
{
    moveFrom(other);
}

RingList::~RingList()
{
    clear();
}

RingList& RingList::operator=(const RingList& other)
{
    if (this != &other) { clear(); copyFrom(other); }
    return *this;
}

RingList& RingList::operator=(RingList&& other) noexcept
{
    if (this != &other) { clear(); moveFrom(other); }
    return *this;
}

RingList& RingList::operator<<=(const std::size_t n)
{
    if (m_size > 1)
    {
        n %= m_size;
        for (std::size_t i = 0; i < n; ++i)
            m_tail = m_tail->next();
    }
    return *this;
}

RingList& RingList::operator>>=(const std::size_t n)
{
    if (m_size > 1)
    {
        n %= m_size;
        *this <<= (m_size - n);
    }
    return *this;
}

RingList RingList::operator<<(std::size_t n) const
{
    RingList copy(*this);
    copy <<= n;
    return copy;
}

RingList RingList::operator>>(const std::size_t n) const
{
    RingList copy(*this);
    copy >>= n;
    return copy;
}

int& RingList::operator[](const std::size_t index)
{
    if (index >= m_size)
        throw std::out_of_range(
            "RingList::operator[]: index " + std::to_string(index) +
            " >= size " + std::to_string(m_size));
    
    return nodeAt(index)->valueRef();
}

const int& RingList::operator[](const std::size_t index) const
{
    if (index >= m_size)
        throw std::out_of_range(
            "RingList::operator[]: index " + std::to_string(index) +
            " >= size " + std::to_string(m_size));
    
    return nodeAt(index)->value();
}

void RingList::pushFront(const int value)
{
    Node* node = new Node(value);
    if (empty())
    {
        node->setNext(node);
        m_tail = node;
    }
    else
    {
        node->setNext(m_tail->next());
        m_tail->setNext(node);
    }
    ++m_size;
}

void RingList::pushBack(const int value)
{
    pushFront(value);
    m_tail = m_tail->next();
}

void RingList::insert(const std::size_t index, const int value)
{
    if (index > m_size)
        throw std::out_of_range(
            "RingList::insert: position " + std::to_string(index) +
            " > size " + std::to_string(m_size));

    if (index == 0) { pushFront(value); return; }
    if (index == m_size) { pushBack(value);  return; }

    Node* prev = nodeAt(index - 1);
    Node* node = new Node(value, prev->next());
    prev->setNext(node);
    ++m_size;
}

void RingList::erase(const std::size_t index)
{
    if (index >= m_size)
        throw std::out_of_range(
            "RingList::erase: index " + std::to_string(index) +
            " >= size " + std::to_string(m_size));

    Node* head = m_tail->next();

    if (m_size == 1)
    {
        delete head;
        m_tail = nullptr;
        m_size = 0;
        return;
    }

    if (index == 0)
    {
        m_tail->setNext(head->next());
        delete head;
    }
    else
    {
        Node* prev = nodeAt(index - 1);
        Node* toDelete = prev->next();
        prev->setNext(toDelete->next());
        if (toDelete == m_tail)
            m_tail = prev;
        delete toDelete;
    }
    --m_size;
}

bool RingList::remove(const int value)
{
    int idx = find(value);
    if (idx < 0) return false;
    erase(static_cast<std::size_t>(idx));
    return true;
}

void RingList::clear()
{
    while (!empty()) erase(0);
}

int RingList::find(const int value) const
{
    if (empty()) return -1;
    Node* cur = m_tail->next();
    for (std::size_t i = 0; i < m_size; ++i)
    {
        if (cur->value() == value)
            return static_cast<int>(i);
        cur = cur->next();
    }
    return -1;
}

std::size_t RingList::size() const { return m_size; }
bool        RingList::empty() const { return m_size == 0; }

std::string RingList::toString() const
{
    if (empty()) return "( empty )";

    std::string s = "( ";
    Node* cur = m_tail->next();
    for (std::size_t i = 0; i < m_size; ++i)
    {
        s += std::to_string(cur->value());
        s += " -> ";
        cur = cur->next();
    }
    s += "... )";
    return s;
}
