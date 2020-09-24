#include <iostream>
#include <algorithm>
#include <memory>

using std::make_shared;
using std::shared_ptr;
using std::string;
using std::move;

#ifndef EX3_MY_SET_H
#define EX3_MY_SET_H

template <class T>
class my_set
{
private:
    class node
    {
    public:
        //ctors
        node() = default;
        explicit node(const T& data) : node(data, nullptr, nullptr) {}
        explicit node(const T& data, shared_ptr<node> l, shared_ptr<node> r) : _data(data), _left(l), _right(r) {}

        //helpers

        //getters//getters//getters//getters//getters//getters//getters//getters//getters//getters//getters
        T& getData()
        {
            return _data;
        }
        shared_ptr<node>& getLeft()
        {
            return _left;
        }
        shared_ptr<node>& getRight()
        {
            return _right;
        }

        //setters//setters//setters//setters//setters//setters//setters//setters
        shared_ptr<node> setLeft(shared_ptr<node> l)
        {
            if(_left) // if the left son exists we'll want to erase it first
            {
                _left = nullptr;
            }
            _left = l ? make_shared<node>(*l) : nullptr;
            return _left;
        }
        shared_ptr<node> setRight(shared_ptr<node> r)
        {
            if(_right) // if the left son exists we'll want to erase it first
            {
                _right = nullptr;
            }
            _right = r ? make_shared<node>(*r) : nullptr;
            return _right;
        }

        void setData(const T& data)
        {
            _data = data;
        }
        //dtor
        ~node() = default;
    private:
        T _data;
        shared_ptr<node> _left;
        shared_ptr<node> _right;
    };
    shared_ptr<node> _root;
    size_t _size;
public:

    // ctors// ctors// ctors// ctors// ctors// ctors// ctors// ctors// ctors// ctors// ctors// ctors
    my_set() : _root(nullptr), _size(0) {}
    my_set(const my_set& other);
    my_set(my_set && other) noexcept;
    template <class InputIterator>
    my_set(InputIterator first, InputIterator last);
    my_set<T>& operator=(my_set<T> other);
    my_set<T>& operator=(my_set<T> && other) noexcept;

    class const_iterator
    {
    public:
        //const_iterator ctor
        const_iterator(const my_set* parent, shared_ptr<node> node_p = nullptr) : _parent(parent), _pointer(node_p) {}

        //const_iterator methods
        virtual T operator*() const
        {
//            if(_pointer)
//            {
//                return _pointer.get()->getData();
//            }
            return _pointer.get()->getData();
        }

        virtual T* operator->() const
        {
            if(!_pointer.get())
            {
                return nullptr;
            }
            return &_pointer.get()->getData();
        }

        virtual const_iterator& operator++()
        {
            _pointer = _parent->inOrderSuccessor(_pointer);
            return *this;
        }

        virtual const_iterator& operator--()
        {
            _pointer = _parent->inOrderPredecessor(_pointer);
            return *this;
        }

        virtual const_iterator operator++(int)
        {
            my_set<T>::const_iterator tmp = *this;
            operator++();
            return tmp;
        }

        virtual const_iterator operator--(int)
        {
            my_set<T>::const_iterator tmp = *this;
            operator--();
            return tmp;
        }

        virtual bool operator==(const const_iterator& rhs) const
        {
            return (_pointer == rhs._pointer);
        }

        virtual bool operator!=(const const_iterator& rhs) const
        {
            return (_pointer != rhs._pointer);
        }

        //getter
        shared_ptr<node> getNodeP() const
        {
            return _pointer;
        }
    protected:
        shared_ptr<node> _pointer;
        const my_set* _parent;
    };

    class const_reverse_iterator : public const_iterator
    {
    public:
        //const_reverse_iterator ctor
        const_reverse_iterator(const my_set* parent, shared_ptr<node> node_p = nullptr)
        : const_iterator(parent, node_p) {}

        //const_reverse_iterator methods
        const_reverse_iterator& operator++() override
        {
            this->_pointer = this->_parent->inOrderPredecessor(this->_pointer);
            return *this;
        }

        const_reverse_iterator& operator--() override
        {
            this->_pointer = this->_parent->inOrderSuccessor(this->_pointer);
            return *this;
        }

        const_iterator operator++(int) override
        {
            my_set<T>::const_reverse_iterator tmp = *this;
            operator++();
            return tmp;
        }

        const_iterator operator--(int) override
        {
            my_set<T>::const_reverse_iterator tmp = *this;
            operator--();
            return tmp;
        }
    };

    //helpers//helpers//helpers//helpers//helpers//helpers//helpers//helpers//helpers//helpers//helpers
    shared_ptr<node> minVal(shared_ptr<node> const root) const;
    shared_ptr<node> inOrderSuccessor(shared_ptr<node> n) const;
    shared_ptr<node> maxVal(shared_ptr<node> const root) const; // TODO root = nullptr?
    shared_ptr<node> inOrderPredecessor(shared_ptr<node> n) const;
    bool isRoot(shared_ptr<node> n) const;

    // getters// getters// getters// getters// getters// getters// getters// getters// getters
    shared_ptr<node> getRoot() const;

    // setters// setters// setters// setters// setters// setters// setters// setters// setters
    void setRoot(shared_ptr<node> root);

    //support//support//support//support//support//support//support//support//support//
    size_t size() const;
    bool empty() const;

    // dtor// dtor// dtor// dtor// dtor// dtor// dtor// dtor// dtor// dtor// dtor// dtor
    ~my_set();

    const_iterator createRoot(const T& val);
    my_set<T>::const_iterator addValue(const T& val);

    // access// access// access// access// access// access// access// access
    std::pair<class const_iterator, bool> insert(const T& val);
    std::pair<class const_iterator, bool> insert(T && val); // TODO code duplication

    //insert with a hint
    const_iterator insert(const_iterator position, const T& val);
    const_iterator insert(const_iterator position, T && val);

    // insert from range
    template<class InputIterator>
    void insert(InputIterator first, InputIterator last);

    const_iterator find(const T& val) const;
    shared_ptr<node> findInsertionPlace(const T& val, shared_ptr<node> parent);
    shared_ptr<node> findParent(const T& val, shared_ptr<node> parent);

    void clear();
    const_iterator erase(const_iterator position);
    size_t erase (const T& val);
    const_iterator erase(const_iterator first, const_iterator last);

    void swap(my_set<T>& x);

    template <class U>
    friend void swap(my_set<U>& left, my_set<U>& right) noexcept;

    //TODO bonus emplace - place build

    //access by const_iterator
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;
    // access by const_reverse_iterator
    const_reverse_iterator crbegin() const noexcept;
    const_reverse_iterator crend() const noexcept;

    friend std::ostream& operator<<(std::ostream& os, const my_set<T>& m_s)
    {
        std::for_each(m_s.cbegin(), m_s.cend(), [&](T val){ os << val << std::endl; });
        return os;
    }
};

#include "my_set.hpp"
#endif