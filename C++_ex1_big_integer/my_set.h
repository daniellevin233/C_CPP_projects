// my_set.h

#ifndef EX1C_MY_SET_H
#define EX1C_MY_SET_H

#include "big_integer.h"

/**
 *  A set of big integers class.
 *  This class represents a set data structure of the big integers numbers
 *
 *  NOTE BONUS NOTE BONUS NOTE BONUS NOTE BONUS NOTE BONUS NOTE BONUS NOTE BONUS NOTE BONUS NOTE
 *
 *  The implementation of the operator<< takes O(N) time complexity regards to the fact
 *  that set implemented as linked sorted list at the stage of initialisation
 *
 *  NOTE BONUS NOTE BONUS NOTE BONUS NOTE BONUS NOTE BONUS NOTE BONUS NOTE BONUS NOTE BONUS NOTE
 */
class my_set
{
private:
    /**
     * A node class
     * This class represents node in linked list for my_set implementation.
     */
    class node
    {
    public:

        // ------------------- constructors -------------------

        /**
         * The default constructor that creates a node with default big_integer and nullptr
         */
        node();

        /**
         * The default copy constructor - there are no deep parameters
         * @param node - node to be copied from
         */
        node(const node& node) = default;

        /**
         * Operator assignment for node
         * @param other_node - other node to be assigned to
         * @return - reference to the node that was assigned
         */
        node& operator=(const node& other_node);

        /**
         * Constructor for node with big_integer to be put into _node_value
         * @param value - big_integer to be initialised into the node
         */
        explicit node(const big_integer& value);

        /**
         * Constructor for node with big_integer to be put into _node_value and pointer to the
         * next node
         * @param value - big_integer to be initialised into the node
         * @param next - pointer to the next node
         */
        explicit node(const big_integer& value, node* next);

        // ------------------- methods -------------------

        /**
         * Method checks if 'this' node contains value as _node_value or not
         * @param value - big_integer to check in the node
         * @return true if value equal to _node_value, false otherwise
         */
        bool isNode(const big_integer& value) const;

        /**
         * Method checks if the given value is in the linked list(that begin on 'this') or not
         * @param value - big_integer to be checked
         * @return true if value is inside one of the following nodes of 'this', false otherwise
         */
        bool isInList(const big_integer& value);

        /**
         * Method adds a node with value as _node_value to the list
         * at this point we already know that node with such a value is inside the list
         * Basically creating a new node
         * @param value - big_integer to be added
         */
        void addToList(const big_integer& value);

        /**
         * Method removes a node with value like _node_value from the list
         * at this point we already know that node with such a value is inside the list
         * @param value - big_integer to be removed
         */
        void removeFromList(const big_integer& value);

        /**
         * Method moves the given node to the next
         * @return pointer to the node representing the next node of the given one
         */
        node* moveNode() const;

        // ------------------- setters -------------------

        /**
         * Setter for the next node to 'this' node
         * @param next_node_ptr - pointer to the node to be linked to
         */
        void setNext(node* next_node_ptr);

        // ------------------- getters -------------------

        /**
         * Getter for _node_value of the node
         * @return reference to the big_integer that is contained in 'this'
         */
        big_integer& getValue();

        // ------------------- destructor -------------------

        /**
         * Default destructor cause we don't have any deep structures
         */
        ~node() = default;
    private:
        big_integer _node_value; /**<_node_value - represents big_integer that is in the node*/
        node* _next; /**<_next - pointer to the next node in the list*/
    };
    node* _head; /**<_head - pointer to the head of the linked list - of my_set*/
    size_t _my_set_size;  /**<_my_set_size - size_t representing the current size of my_set -
                            number of elements that are holden up inside of it*/
    big_integer _sum; /**<_sum - big_integer representing the sum of all the values that saved in
                            the nodes of linked list representing my_set=*/
public:

    // ------------------- constructors -------------------

    /**
     * The default constructor that creates an empty set
     */
    my_set();

    /**
     * The copy constructor for my_set
     * @param other_my_set - my_set to be copied from
     */
    my_set(const my_set& other_my_set);

    /**
     * Operator assignment for my_set
     * @param other_set - other my_set to be assigned to
     * @return - reference to the my_set that was assigned
     */
    my_set& operator= (const my_set& other_set);

    // ------------------- methods -------------------

    /**
     * Method checks if the my_set is empty or not
     * @return true if number of elements is zero, false otherwise
     */
    bool isEmpty() const;

    /**
     * Method checks if the bug_integer with value is in the set or not
     * @param value - big_integer to be found
     * @return - true if my_set contains element with the same value, false otherwise
     */
    bool is_in_set(const big_integer& value) const;

    /**
     * The method adds big_integer with value to the my_set
     * @param value - big_integer to be added
     * @return - false if the given value is already in the set, true if it was successfully added
     */
    bool add(big_integer value);

    /**
     * The method removes big_integer with value from the my_set
     * @param value - big_integer to be removed
     * @return - false if the given value is already in the set, true if it was successfully removed
     */
    bool remove(const big_integer& value);

    /**
     * The method return sum of all the elements that are in the set
     * @return big_integer representing the whole sum of set values
     */
    big_integer sum_set() const;

    // ------------------- operators -------------------

    /**
     * The subtraction for my_sets - includes all the elements that are in 'this' but not in other
     * @param other_set - my_set which elements have to be excluded from the result set
     * @return new my_set that contains all the elements that are in 'this' but not in other
     */
    my_set operator- (const my_set& other_set) const;

    /**
     * The union for my_sets - includes all the elements that are in 'this' and in other
     * @param other_set - my_set which elements have to be added to the result set in addition
     * to 'this' elements
     * @return new my_set that contains all the elements that are in 'this' and in other without
     * reduplications
     */
    my_set operator| (const my_set& other_set) const;

    /**
     * The intersection for my_sets - includes all the elements that are both in 'this' and in other
     * @param other_set - my_set which elements have to be intersected with 'this' elements
     * @return new my_set that contains all the elements that are both in 'this' and in other
     */
    my_set operator& (const my_set& other_set) const;

    /**
     * The operator for representing my_set into stream os, the elements represented in the
     * increasing order
     * @param os - stream for passing the representation into it
     * @param my_set - my_set to be represented
     * @return reference to the stream that was updated
     */
    friend std::ostream& operator<< (std::ostream& os, const my_set& my_set);

    // ------------------- destructor -------------------

    /**
     * Destructor cleans the instance of my_set and delete the memory that was allocated for it
     */
    ~my_set();
};

#endif //EX1C_MY_SET_H