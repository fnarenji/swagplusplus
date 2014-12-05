#include "CList2.h"

using namespace std;
using namespace nsSdD;

template<typename T>
CList<T>::CList() noexcept : m_head(std::make_shared<CNode>(T(), nullptr, nullptr)),
                             m_tail(std::make_shared<CNode>(T(), nullptr, m_head))
{
    m_head->setNext(m_tail);
}

template<typename T>
CList<T>::CList(size_t n) noexcept
        : m_head(std::make_shared<CNode>(T(), nullptr, nullptr)),
          m_tail(std::make_shared<CNode>(T(), nullptr, m_head))
{
    m_head->setNext(m_tail);

    for (size_t i = 0; i < n; i++)
    {
        CNodePtr ptr = std::make_shared<CNode>(T(), nullptr, nullptr);

        ptr->setNext(m_tail);
        ptr->setPrevious(m_tail->getPrevious());

        m_tail->getPrevious()->setNext(ptr);
        m_tail->setPrevious(ptr);

        ++m_size;
    }
}

template<typename T>
CList<T>::CList(size_t n, const T &val) noexcept
        : m_head(std::make_shared<CNode>(T(), nullptr, nullptr)),
          m_tail(std::make_shared<CNode>(T(), nullptr, m_head))
{
    m_head->setNext(m_tail);

    for (size_t i = 0; i < n; i++)
    {
        CNodePtr ptr = std::make_shared<CNode>(val, nullptr, nullptr);
        CNodePtr LastCreated = m_tail->getPrevious();

        ptr->setNext(m_tail);
        ptr->setPrevious(LastCreated);

        LastCreated->setNext(ptr);
        m_tail->setPrevious(ptr);

        ++m_size;
    }
}

template<typename T>
CList<T>::CList(const CList<T> &x) noexcept
{
    m_head = x.getHead();
    m_tail = x.getTail();
    m_size = x.size();

    for (CNodePtr p = x.getHead(); p; p = p->getNext())
    {
        CNodePtr temp = std::make_shared<CNode>(p->getInfo(), p->getNext(), p->getPrevious());
    }
}

template<typename T>
void CList<T>::assign(unsigned n, const T &val) noexcept
{
    if (this->size() == 0)
    {
        for (size_t i = 0; i < n; i++)
        {
            CNodePtr ptr = std::make_shared<CNode>(val, nullptr, nullptr);
            CNodePtr LastCreated = m_tail->getPrevious();

            ptr->setNext(m_tail);
            ptr->setPrevious(LastCreated);

            LastCreated->setNext(ptr);
            m_tail->setPrevious(ptr);

            ++m_size;
        }
    }
}

template<typename T>
template<class InputIterator>
void CList<T>::assign(InputIterator first, InputIterator last)
{
    CNodePtr prec = m_head;
    for(InputIterator tmp = first; tmp <= last; ++tmp)
    {
        prec->setNext(tmp);

        CNodePtr add = new CNode(*tmp);
        add->setPrevious(prec);
        add->setNext(prec->getNext());

        m_tail->setPrevious(add);

        ++m_size;
        prec = add;
    }
}

template<typename T>
void CList<T>::emplace_front(T val) noexcept
{
    CNodePtr ptr = std::make_shared<CNode>(val, nullptr, nullptr);

    ptr->setPrevious(m_head);
    ptr->setNext(m_head->getNext());

    (m_head->getNext())->setPrevious(ptr);

    m_head->setNext(ptr);

    ++m_size;
}

template<typename T>
void CList<T>::pop_front() noexcept
{
    CNodePtr del = m_head->getNext();
    m_head->setNext(del->getNext());

    (del->getNext())->setPrevious(m_head);

    del->setPrevious(nullptr);
    del->setNext(nullptr);

    --m_size;
}

template<typename T>
void CList<T>::push_front(const T &x) noexcept
{
    CNodePtr add = std::make_shared<CNode>(x, nullptr, nullptr);

    add->setNext(m_head->getNext());
    add->setPrevious(m_head);
    add->getNext()->setPrevious(add);
    m_head->setNext(add);

    ++m_size;
}

template<typename T>
void CList<T>::push_back(const T &x) noexcept
{
    CNodePtr add = std::make_shared<CNode>(x, nullptr, nullptr);
    CNodePtr LastCreated = m_tail->getPrevious();

    add->setNext(m_tail);
    add->setPrevious(LastCreated);

    LastCreated->setNext(add);
    m_tail->setPrevious(add);

    ++m_size;
}

template<typename T>
void CList<T>::pop_back() noexcept
{
    CNodePtr del = m_tail->getPrevious();
    m_tail->setPrevious(del->getPrevious());

    del->getPrevious()->setNext(m_tail);

    del->setPrevious(nullptr);
    del->setNext(nullptr);

    --m_size;
}

template<typename T>
void CList<T>::emplace(CNodePtr Prec, T val) noexcept
{
    CNodePtr add = make_shared<CNode>(val, Prec, Prec->getNext());

    Prec->getNext()->setPrevious(add);
    Prec->setNext(add);

    ++m_size;
}

template<typename T>
void CList<T>::erase(CNodePtr del) noexcept
{
    del->getNext()->setPrevious(del->getPrevious());
    del->getPrevious()->setNext(del->getNext());

    del->setPrevious(nullptr);
    del->setNext(nullptr);

    --m_size;
}

template<typename T>
void CList<T>::resize(unsigned n, const T& val /*= T()*/) noexcept
{
    if(m_size == n)
        return;

    if(m_size > n)
    {
        CNodePtr ptr = m_head;
        for(size_t i = 0; i < n; ++i)
            ptr = ptr->getNext();

        ptr->setNext(m_tail);
        m_tail->setPrevious(ptr);

        m_size = n;

        return;
    }

    CNodePtr ptr = m_head;
    for(size_t i = 0; i < m_size; ++i)
        ptr = ptr->getNext();

    for(size_t i = 0; i < n - m_size; ++i)
    {
        CNodePtr add = make_shared<CNode>(val, ptr, ptr->getNext());
        ptr->setNext(add);
        m_tail->setPrevious(add);
        ptr = add;
    }

    m_size = n;
}

template<typename T>
void CList<T>::swap(nsSdD::CList<T> &x) noexcept
{
    CNodePtr ptr = m_head;
    m_head->setNext(x.getHead()->getNext());
    x.getHead()->setNext(ptr->getNext());

    ptr = m_tail;
    m_tail->setPrevious(x.getTail()->getPrevious());
    x.getTail()->setPrevious(ptr->getPrevious());

    size_t tmp = m_size;
    m_size = x.size();

    x.m_size = this->m_size;
}

template<typename T>
void CList<T>::clear() noexcept
{
    m_head->setNext(m_tail);
    m_tail->setPrevious(m_head);

    m_size = 0;
}

template<typename T>
void CList<T>::remove(const T& val) noexcept
{
    for (CNodePtr a = m_head; a; a = a->getNext())
    {
        if (a->getInfo() == val)
        {
            (a->getPrevious())->setNext(a->getNext());
            (a->getNext())->setPrevious(a->getPrevious());
            a->setNext(nullptr);
            a->setPrevious(nullptr);
            return;
        }
    }
}

template<typename T>
template<class Predicate>
void CList<T>::remove_if(Predicate pred) noexcept
{
    for (CNodePtr a = m_head; a; a = a->getNext())
    {
        if (! pred(a))
        {
            (a->getPrevious())->setNext(a->getNext());
            (a->getNext())->setPrevious(a->getPrevious());
            a->setNext(nullptr);
            a->setPrevious(nullptr);
        }
    }
}

template<typename T>
void CList<T>::reverse() noexcept
{
    CNodePtr tmp = m_head;
    m_head->setNext(m_tail->getPrevious());
    m_tail->setPrevious(tmp->getNext());

    for(size_t i = 0; i < m_size; ++i)
    {
        CNodePtr ptr = tmp->getNext()->getPrevious();
        tmp->getNext()->setPrevious(tmp->getNext()->getNext());
        tmp->getNext()->setNext(ptr);

        tmp = tmp->getNext();
    }
}

template<typename T>
void CList<T>::emplace_back(T val) noexcept
{
    CNodePtr a = make_shared<CNode>(val,m_tail->getPrevious(),m_tail);
    (m_tail->getPrevious())->setNext(a);
    m_tail->setPrevious(a);

    ++m_size;
}

template<typename T>
typename CList<T>::iterator CList<T>::insert(typename CList<T>::const_iterator position, T const &val) noexcept
{
    CNodePtr tmp = make_shared<CNode>(val);
    tmp->setNext(*position);
    tmp->setPrevious(position->getPrevious());
    (position->getPrevious())->setNext(tmp);
    position->setPrevious(tmp);

    ++m_size;
}
