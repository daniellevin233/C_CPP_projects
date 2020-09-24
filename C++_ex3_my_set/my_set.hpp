#include <iostream>
#include <algorithm>
#include "my_set.h"

// functions of my_set// functions of my_set// functions of my_set// functions of my_set// functions of my_set

template <class T>
my_set<T>::my_set(const my_set<T>& other) : my_set(other.cbegin(), other.cend()) {}

template <class T>
my_set<T>::my_set(my_set<T> && other) noexcept
{
    _root = other._root;
    other._root = nullptr;
    _size = other._size;
}

template <class T>
my_set<T>& my_set<T>::operator=(my_set<T> other)
{
    swap(other);
    return *this;
}

template <class T>
my_set<T>& my_set<T>::operator=(my_set<T> && other) noexcept
{
    swap(other);
    return *this;
}

template <class T>
template <class InputIterator>
my_set<T>::my_set(InputIterator first, InputIterator last) : my_set()
{
    for(; first != last; ++first)
    {
        insert(*first);
    }
}

template <class T>
shared_ptr<typename my_set<T>::node> my_set<T>::minVal(shared_ptr<my_set<T>::node> const root) const
{
    if(!root)
    {
        return nullptr;
    }
    return (root.get()->getLeft()) ? (minVal(root.get()->getLeft())) : root;
}

template <class T>
shared_ptr<typename my_set<T>::node> my_set<T>::inOrderSuccessor(shared_ptr<my_set<T>::node> n) const
{
    if(!n.get()) // TODO exceptions tree
    {
        return n;
    }
    if(n.get()->getRight())
    {
        return minVal(n.get()->getRight());
    }
    shared_ptr<node> cur_root = _root, succ = nullptr;
    while(cur_root.get())
    {
        if(n.get()->getData() < cur_root.get()->getData())
        {
            succ = cur_root;
            cur_root = cur_root.get()->getLeft();
        }
        else if(n.get()->getData() > cur_root.get()->getData())
        {
            cur_root = cur_root.get()->getRight();
        }
        else
        {
            break;
        }
    }
    return succ;
}

template<class T>
shared_ptr<typename my_set<T>::node> my_set<T>::maxVal(shared_ptr<my_set<T>::node> const root) const // TODO root = nullptr?
{
    if(!root)
    {
        return nullptr;
    }
    return (root.get()->getRight()) ? (maxVal(root.get()->getRight())) : root;
}

template <class T>
shared_ptr<typename my_set<T>::node> my_set<T>::inOrderPredecessor(shared_ptr<my_set<T>::node> n) const
{
    if(!n.get())
    {
        return maxVal(_root);
    }
    if(n.get()->getLeft())
    {
        return maxVal(n.get()->getLeft());
    }
    shared_ptr<node> cur_root = _root, pred = nullptr;
    while(cur_root.get())
    {
        if(n.get()->getData() < cur_root.get()->getData())
        {
            cur_root = cur_root.get()->getLeft();
        }
        else if(n.get()->getData() > cur_root.get()->getData())
        {
            pred = cur_root;
            cur_root = cur_root.get()->getRight();
        }
        else
        {
            break;
        }
    }
    return pred;
}

template <class T>
shared_ptr<typename my_set<T>::node> my_set<T>::getRoot() const
{
    return _root;
}

template <class T>
void my_set<T>::setRoot(shared_ptr<my_set<T>::node> root)
{
    if(_root)
    {
        _root = nullptr;
    }
    _root = root;
}

template <class T>
size_t my_set<T>::size() const
{
    return _size;
}

template <class T>
bool my_set<T>::empty() const
{
    return (_size == 0);
}

template <class T>
my_set<T>::~my_set()
{
    clear();
}

template <class T>
typename my_set<T>::const_iterator my_set<T>::createRoot(const T& val)
{
    shared_ptr<node> new_node_p = make_shared<node>(val);
    setRoot(new_node_p);
    const_iterator res_c_iter(this, new_node_p);
    ++_size;
    return res_c_iter;
}

template <class T>
typename my_set<T>::const_iterator my_set<T>::addValue(const T& val)
{
    shared_ptr<node> new_node_p = make_shared<node>(val);
    shared_ptr<node> parent = findInsertionPlace(val, _root);
    new_node_p = (val < parent.get()->getData()) ? parent.get()->setLeft(new_node_p) :
    parent.get()->setRight(new_node_p);
    const_iterator res_c_it(this, new_node_p);
    ++_size;
    return res_c_it;
}

template <class T>
std::pair<class my_set<T>::const_iterator, bool> my_set<T>::insert(const T& val)
{
    if(empty())
    {
        return std::pair<const_iterator, bool>(createRoot(val), true);
    }
    my_set<T>::const_iterator find_res = find(val);
    if(find_res.getNodeP()) // find returned some non trivial iterator
    {
        return std::pair<const_iterator, bool>(find_res, false);
    }
    else
    {
        return std::pair<const_iterator, bool>(addValue(val), true);
    }
}

template <class T>
std::pair<class my_set<T>::const_iterator, bool> my_set<T>::insert(T && val)
{
    return insert(val);
}

template <class T>
typename my_set<T>::const_iterator my_set<T>::insert(my_set<T>::const_iterator position, T && val)
{
    my_set<T>::const_iterator find_res = find(val);
    if(find_res.getNodeP())
    {
        return find_res;
    }
    shared_ptr<node> new_node = make_shared<node>(val);
    shared_ptr<node> hint = position.getNodeP();
    shared_ptr<node> prev = inOrderPredecessor(hint);
    if(hint && prev && (hint->getData() > val) && (prev->getData() < val)) // the hint is good
    {
        if(prev->getRight())
        {
            new_node->setRight(hint);
        }
        new_node = prev->setRight(new_node);
        ++_size;
    }
    else
    {
        return insert(val).first;
    }
    return my_set<T>::const_iterator(this, new_node);
}

template <class T>
template <class InputIterator>
void my_set<T>::insert(InputIterator first, InputIterator last)
{
    for(; first != last; ++first)
    {
        insert(*first);
    }
}

template <class T>
typename my_set<T>::const_iterator my_set<T>::find(const T& val) const
{
    shared_ptr<node> cur_root = _root;
    while(cur_root.get())
    {
        if(cur_root.get()->getData() == val)
        {
            return my_set<T>::const_iterator(this, cur_root);
        }
        else if(cur_root.get()->getData() > val)
        {
            cur_root = cur_root.get()->getLeft();
        }
        else
        {
            cur_root = cur_root.get()->getRight();
        }
    }
    return my_set<T>::cend();
}

template <class T>
shared_ptr<typename my_set<T>::node> my_set<T>::findInsertionPlace(const T& val,
                   shared_ptr<node> parent)
{
    shared_ptr<node> insertPlace = (val < parent.get()->getData()) ? parent.get()->getLeft() :
           parent.get()->getRight();
    return insertPlace ? findInsertionPlace(val, insertPlace) : parent;
}

template <class T>
shared_ptr<typename my_set<T>::node> my_set<T>::findParent(const T& val,
                   shared_ptr<my_set<T>::node> parent)
{
    if(val == _root->getData())
    {
        return _root;
    }
    shared_ptr<node> insertPlace = (val < parent.get()->getData()) ? parent.get()->getLeft() :
                                   parent.get()->getRight();
    return (insertPlace->getData() != val) ? findParent(val, insertPlace) : parent;
}

template <class T>
void my_set<T>::clear()
{
    for(auto first = cbegin(); first != cend(); ++first)
    {
        erase(first);
    }
}

template <class T>
bool my_set<T>::isRoot(shared_ptr<node> n) const
{
    return (_root->getData() == n->getData());
}

template <class T>
typename my_set<T>::const_iterator my_set<T>::erase(const_iterator position)
{
    size_t tmp_size = _size - 1;
//    shared_ptr<node> erase_node = find(*position).getNodeP();
    shared_ptr<node> erase_node = position.getNodeP();
    shared_ptr<node> succ = inOrderSuccessor(erase_node);
    shared_ptr<node> parent_of_erase = findParent(erase_node->getData(), _root);
    bool erase_is_left_son = (parent_of_erase->getData() > erase_node->getData());
    if (!erase_node->getLeft() && !erase_node->getRight()) // the erase node without sons
    {
        if(isRoot(erase_node))
        {
            _root = nullptr;
            succ = nullptr;
        }
        else
        {
            erase_is_left_son ? parent_of_erase->setLeft(nullptr) : parent_of_erase->setRight(nullptr);
        }
    }
    else if (!erase_node->getLeft() || !erase_node->getRight()) // the erase node with one son
    {
        if(isRoot(erase_node))
        {
            shared_ptr<node> new_root = erase_node->getLeft() ? erase_node->getLeft() : erase_node->getRight();
            setRoot(new_root);
        }
        else
        {
            shared_ptr<node> son_to_connect = erase_node->getLeft() ? erase_node->getLeft() :
                                              erase_node->getRight();
            erase_is_left_son ? parent_of_erase->setLeft(son_to_connect) :
            parent_of_erase->setRight(son_to_connect);
            erase_node->getLeft() ? erase_node->setLeft(nullptr) : erase_node->setRight(nullptr);
        }
    }
    else // the erase node has two sons
    {
        T tmp_data = succ->getData();
        erase(const_iterator(this, succ));
        erase_node->setData(tmp_data);
        succ = inOrderSuccessor(erase_node);
    }
    _size = tmp_size;
    return const_iterator(this, succ);
}

template <class T>
size_t my_set<T>::erase(const T& val)
{
    const_iterator find_res = find(val);
    if(!find_res.getNodeP())
    {
        return 0;
    }
    erase(find_res);
    return 1;
}

template <class T>
typename my_set<T>::const_iterator my_set<T>::erase(const_iterator first, const_iterator last)
{
    for(; first != last; ++first)
    {
        erase(first);
    }
}

template <class T>
void swap(my_set<T>& left, my_set<T>& right) noexcept
{
    std::swap(left._root, right._root);
//    std::swap(left._size, right._size);
    size_t tmp = left._size;
    left._size = right._size;
    right._size = tmp;
}

template <class T>
void my_set<T>::swap(my_set<T>& x)
{
//    swap(*this, x);
    std::swap(_root, x._root);
    size_t tmp = _size;
    _size = x._size;
    x._size = tmp;
}

template <class T>
typename my_set<T>::const_iterator my_set<T>::cbegin() const noexcept
{
    if(empty())
    {
        return const_iterator(this);
    }
    return const_iterator(this, minVal(_root));
}

template <class T>
typename my_set<T>::const_iterator my_set<T>::cend() const noexcept
{
    return const_iterator(this);
}

template <class T>
typename my_set<T>::const_reverse_iterator my_set<T>::crbegin() const noexcept
{
    if(empty())
    {
        return crend();
    }
    return const_reverse_iterator(this, maxVal(_root));
}

template <class T>
typename my_set<T>::const_reverse_iterator my_set<T>::crend() const noexcept
{
    return const_reverse_iterator(this);
}

// functions of const_iterator// functions of const_iterator// functions of const_iterator// functions of const_iterator
//template <class T>
//T my_set<T>::const_iterator::operator*() const
//{
//    return _pointer->getData();
//}

//template <class T>
//T* my_set<T>::const_iterator::operator->() const
//{
//    return &_pointer->getData();
//}

//template <class T>
//my_set<T>::const_iterator& my_set<T>::const_iterator::operator++()
//{
//    _pointer = _parent->inOrderSuccessor(_pointer);
//    return *this;
//}

//template <class T>
//my_set<T>::const_iterator& my_set<T>::const_iterator::operator--()
//{
//    _pointer = _parent->inOrderPredecessor(_pointer);
//    return *this;
//}

//template <class T>
//my_set::const_iterator my_set<T>::const_iterator::operator++(int)
//{
//    my_set<T>::const_iterator tmp = *this;
//    operator++();
//    return tmp;
//}

//template <class T>
//my_set::const_iterator my_set<T>::const_iterator::operator--(int)
//{
//    my_set<T>::const_iterator tmp = *this;
//    operator--();
//    return tmp;
//}

//template <class T>
//bool my_set<T>::const_iterator::operator==(my_set<T>::const_iterator& rhs) const
//{
//    return (_pointer == rhs._pointer);
//}

//template <class T>
//bool my_set<T>::const_iterator::operator!=(my_set<T>::const_iterator& rhs) const
//{
//    return (_pointer != rhs._pointer);
//}

// functions of const_reverse_iterator// functions of const_reverse_iterator// functions of const_reverse_iterator//

//template <class T>
//my_set<T>::const_reverse_iterator& my_set<T>::const_reverse_iterator::operator++()
//{
//    _pointer = _parent->inOrderPredecessor(_pointer);
//    return *this;
//}
//
//template <class T>
//my_set<T>::const_reverse_iterator& my_set<T>::const_reverse_iterator::operator--()
//{
//    _pointer = _parent->inOrderSuccessor(_pointer);
//    return *this;
//}
//
//template <class T>
//my_set<T>::const_iterator my_set<T>::const_reverse_iterator::operator++(int)
//{
//    my_set<T>::const_reverse_iterator tmp = *this;
//    operator++();
//    return tmp;
//}
//
//template <class T>
//my_set<T>::const_iterator my_set<T>::const_reverse_iterator::operator--(int)
//{
//    my_set<T>::const_reverse_iterator tmp = *this;
//    operator--();
//    return tmp;
//}

template<class T>
std::ostream& operator<<(std::ostream& os, const my_set<T> m_s)
{
    for(typename my_set<T>::const_iterator first = m_s.cbegin(); m_s.cend() != first; ++first)
    {
        os << *first << std::endl;
    }
    return os;
}