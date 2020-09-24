// my_set.cpp

#include <iostream>
#include "my_set.h"
#include "big_integer.h"

// --------------------------------------------------------------------------------------
// This file contains the implementation of the class my_set.
// --------------------------------------------------------------------------------------

/**
 * The default constructor that creates a node with default big_integer and nullptr
 */
my_set::node::node()
:node(*new big_integer(), nullptr) {}

/**
 * Constructor for node with big_integer to be put into _node_value
 * @param value - big_integer to be initialised into the node
 */
my_set::node::node(const big_integer& value)
:node(value, nullptr) {}

/**
 * Constructor for node with big_integer to be put into _node_value and pointer to the
 * next node
 * @param value - big_integer to be initialised into the node
 * @param next - pointer to the next node
 */
my_set::node::node(const big_integer& value, node* next)
:_node_value(big_integer(value)), _next(next) {}

/**
 * Operator assignment for node
 * @param other_node - other node to be assigned to
 * @return - reference to the node that was assigned
 */
my_set::node& my_set::node::operator=(const node& other_node)
{
    if(this != &other_node)
    {
        delete &_node_value;
        delete _next;
        _node_value = *new big_integer(other_node._node_value);
        _next = new node(*other_node._next);
    }
    return *this;
}

/**
 * Getter for _node_value of the node
 * @return reference to the big_integer that is contained in 'this'
 */
big_integer& my_set::node::getValue()
{
    return _node_value;
}

/**
 * The default constructor that creates an empty set
 */
my_set::my_set()
{
    _head = nullptr;
    _my_set_size = 0;
    _sum = big_integer();
}

/**
 * The copy constructor for my_set
 * @param other_my_set - my_set to be copied from
 */
my_set::my_set(const my_set& other_my_set)
:my_set()
{
    if (other_my_set._head != nullptr)
    {
        _head = new node(*other_my_set._head);
        node *cur = _head;
        node* cur_other = other_my_set._head->moveNode();
        while(cur_other)
        {
            cur->setNext(new node(*cur_other));
            cur = cur->moveNode();
            cur_other = cur_other->moveNode();
        }
        _my_set_size = other_my_set._my_set_size;
        _sum = big_integer(other_my_set._sum);
    }
}

/**
 * Operator assignment for my_set
 * @param other_set - other my_set to be assigned to
 * @return - reference to the my_set that was assigned
 */
my_set& my_set::operator=(const my_set& other_set)
{
    if (this != &other_set)
    {
        this->~my_set();
        _head = new node(*other_set._head);
        node *cur = _head;
        node* cur_other = other_set._head->moveNode();
        while(cur_other)
        {
            cur->setNext(new node(*cur_other));
            cur = cur->moveNode();
            cur_other = cur_other->moveNode();
        }
        _my_set_size = other_set._my_set_size;
        _sum = big_integer(other_set._sum);
    }
    return *this;
}

/**
 * Setter for the next node to 'this' node
 * @param next_node_ptr - pointer to the node to be linked to
 */
void my_set::node::setNext(node* next_node_ptr)
{
    _next = next_node_ptr ? next_node_ptr : nullptr;
}

/**
 * Method checks if 'this' node contains value as _node_value or not
 * @param value - big_integer to check in the node
 * @return true if value equal to _node_value, false otherwise
 */
bool my_set::node::isNode(const big_integer& value) const
{
    return (_node_value == value);
}

/**
 * Method moves the given node to the next
 * @return pointer to the node representing the next node of the given one
 */
my_set::node* my_set::node::moveNode() const
{
    return ((this != nullptr) ? _next : nullptr);
}

/**
 * Method checks if the given value is in the linked list(that begin on 'this') or not
 * @param value - big_integer to be checked
 * @return true if value is inside one of the following nodes of 'this', false otherwise
 */
bool my_set::node::isInList(const big_integer& value)
{
    node* cur = this;
    while(cur != nullptr)
    {
        if (cur->isNode(value))
        {
            return true;
        }
        cur = cur->moveNode();
    }
    return false;
}

/**
 * Method adds a node with value as _node_value to the list
 * at this point we already know that node with such a value is inside the list
 * Basically creating a new node
 * @param value - big_integer to be added
 */
void my_set::node::addToList(const big_integer& value)
{
    node *prev = this, *cur = _next;
    while(cur && (value > cur->_node_value))
    {
        prev = prev->moveNode();
        cur = cur->moveNode();
    }
    node* new_node;
    new_node = new node(value, cur);
    prev->setNext(new_node);
}

/**
 * Method checks if the my_set is empty or not
 * @return true if number of elements is zero, false otherwise
 */
bool my_set::isEmpty() const
{
    return (_my_set_size == 0);
}

/**
 * Method checks if the bug_integer with value is in the set or not
 * @param value - big_integer to be found
 * @return - true if my_set contains element with the same value, false otherwise
 */
bool my_set::is_in_set(const big_integer &value) const
{
    return _head->isInList(value);
}

/**
 * The method adds big_integer with value to the my_set
 * @param value - big_integer to be added
 * @return - false if the given value is already in the set, true if it was successfully added
 */
bool my_set::add(big_integer value)
{
    if(this->isEmpty())
    {
        _head = new node(value);
    }
    else if(is_in_set(value))
    {
        return false;
    }
    else if(value < _head->getValue()) // the add value has to be the new head of the set
    {
        _head = new node(value, _head);
    }
    else // the add value will take place somewhere in the set
    {
        _head->addToList(value);
    }
    _sum += value;
    _my_set_size++;
    return true;
}

/**
 * Method removes a node with value like _node_value from the list
 * at this point we already know that node with such a value is inside the list
 * @param value - big_integer to be removed
 */
void my_set::node::removeFromList(const big_integer& value)
{
    node *prev = this, *cur = _next;
    while(cur->_node_value != value)
    {
        prev = prev->moveNode();
        cur = cur->moveNode();
    }
    prev->setNext(cur->_next);
    delete cur;
}

/**
 * The method removes big_integer with value from the my_set
 * @param value - big_integer to be removed
 * @return - false if the given value is already in the set, true if it was successfully removed
 */
bool my_set::remove(const big_integer& value)
{
    if(isEmpty() || !is_in_set(value)) // the remove value is not in the set
    {
        return false;
    }
    else if(_head->getValue() == value) // the remove value is the head
    {
        node* tmp = _head->moveNode();
        delete _head;
        _head = tmp;
    }
    else // the remove value is inside of the set
    {
        _head->removeFromList(value);
    }
    _sum -= value;
    _my_set_size--;
    return true;
}

/**
 * The method return sum of all the elements that are in the set
 * @return big_integer representing the whole sum of set values
 */
big_integer my_set::sum_set() const
{
    return _sum;
}

/**
 * The subtraction for my_sets - includes all the elements that are in 'this' but not in other
 * @param other_set - my_set which elements have to be excluded from the result set
 * @return new my_set that contains all the elements that are in 'this' but not in other
 */
my_set my_set::operator- (const my_set& other_set) const
{
    my_set result_set;
    node* cur = _head;
    while(cur)
    {
        if(!other_set.is_in_set(cur->getValue()))
        {
            result_set.add(cur->getValue());
        }
        cur = cur->moveNode();
    }
    return result_set;
}

/**
 * The union for my_sets - includes all the elements that are in 'this' and in other
 * @param other_set - my_set which elements have to be added to the result set in addition
 * to 'this' elements
 * @return new my_set that contains all the elements that are in 'this' and in other without
 * reduplications
 */
my_set my_set::operator| (const my_set& other_set) const
{
    my_set result_set = *this;
    node* cur = other_set._head;
    while(cur)
    {
        if(!is_in_set(cur->getValue()))
        {
            result_set.add(cur->getValue());
        }
        cur = cur->moveNode();
    }
    return result_set;
}

/**
 * The intersection for my_sets - includes all the elements that are both in 'this' and in other
 * @param other_set - my_set which elements have to be intersected with 'this' elements
 * @return new my_set that contains all the elements that are both in 'this' and in other
 */
my_set my_set::operator& (const my_set& other_set) const
{
    my_set result_set;
    node* cur = _head;
    while(cur)
    {
        if(other_set.is_in_set(cur->getValue()))
        {
            result_set.add(cur->getValue());
        }
        cur = cur->moveNode();
    }
    return result_set;
}

/**
 * The operator for representing my_set into stream os, the elements represented in the
 * increasing order
 * @param os - stream for passing the representation into it
 * @param my_set - my_set to be represented
 * @return reference to the stream that was updated
 */
std::ostream& operator<< (std::ostream& os, const my_set& my_set)
{
    if(my_set.isEmpty())
    {
        os << std::endl;
    }
    else
    {
        my_set::node* cur = my_set._head;
        while(cur)
        {
            os << cur->getValue() << std::endl;
            cur = cur->moveNode();
        }
    }
    return os;
}

/**
 * Destructor cleans the instance of my_set and delete the memory that was allocated for it
 */
my_set::~my_set()
{
    if(_head)
    {
        node* prev = _head;
        node* cur = prev->moveNode();
        while(prev)
        {
            delete prev;
            prev = cur;
            cur = cur->moveNode();
        }
    }
}