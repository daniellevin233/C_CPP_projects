// big_integer.h

#include <string>
#define TENS_VALUE 10
#define NEGATIVE_CHAR '-'
#define NEGATIVE_STR "-"
#define NULL_STR "0"
#define NULL_CHAR '0'

#ifndef EX1C_BIG_INTEGER_H
#define EX1C_BIG_INTEGER_H

/**
 *  A big integer class.
 *  This class represents a maximal integer value that computer capacity allows to hold
 */
class big_integer
{
private:
    /**
     * A my string class
     * This class represents my_string for big_integer implementation.
     */
    class my_string
    {
    public:

        // ------------------- constructors -------------------

        /**
         * The default constructor for my_string that doesn't get anything and set my_string to "0"
         */
        my_string();

        /**
         * The copy constructor for  my_strings = default - there are no deep data structures
         * @param otherMyStr - object of type my_string to be copied
         */
        my_string(const my_string &otherMyString) = default;

        /**
         * Constructor for my_string with string (std)
         * @param std_str - standard string to be passed into my_string object
         */
        explicit my_string(const std::string& std_str);

        /**
         * Constructor for my_string with string (std) and boolean value (sign)
         * @param std_str - @see previous constructor
         * @param sign - boolean value representing sign of the number @see _sign
         */
        explicit my_string(const std::string& std_str, bool& sign);

        // ------------------- arithmetic operators  -------------------

        /**
         * Operator assignment for my_strings
         * @param myStrRhs - other my_string to be assigned to
         * @return - reference to the my_string that was assigned
         */
        my_string& operator= (const my_string& myStrRhs);

        /**
         * Operator plus - Sum of two my_strings
         * @param other_my_str - my_string to be added to 'this'
         * @return new my_string representing the sum of this and other
         */
        my_string operator+ (const my_string& other_my_str) const;

        /**
         * Operator plus-equal - assigning to this sum of itself and other
         * @param other_my_str - my_string to be added to 'this'
         * @return reference to my_string - updated my_string ('this')
         * representing the sum of itself before operation and other my_string
         */
        my_string& operator+= (const my_string& other_my_str);

        /**
         * Operator minus - difference between two my_strings
         * @param other_my_str - my_string to be subtracted from 'this'
         * @return new my_string representing the difference of this and other
         */
        my_string operator- (const my_string& other_my_str) const;

        /**
         * Operator multiplication - multiplication of two my_strings
         * @param other_my_str - my_string to be multiplied on 'this'
         * @return new my_string - representing multiplication of 'this' and other
         */
        my_string operator* (const my_string& other_my_str) const;

        /**
         * Operator division - division of two my_strings - without remainder (like integers)
         * @param other_my_str - my_string that divides 'this' my_string
         * @return new my_string - representing division of 'this' by other
         */
        my_string operator/ (const my_string& other_my_str) const;

        /**
         * Operator modulus - remainder of division of 'this' by other
         * @param other_my_str - my_string that divides 'this' my_string
         * @return new my_string - representing remainder of division of 'this' by other (modulus)
         */
        my_string operator% (const my_string& other_my_str) const;

        // ------------------- boolean operators -------------------

        /**
         * Boolean comparison operator for my_strings
         * @param otherMyStr - my_string to be compared with
         * @return - true if this and otherMyStr are equal, false otherwise
         */
        bool operator== (const big_integer::my_string& otherMyStr) const;

        /**
         * Boolean operator "smaller" for my_strings
         * @param otherMyStr - my_string to be compared with
         * @return - true if this smaller than otherMyStr, false otherwise
         */
        bool operator< (const big_integer::my_string& otherMyStr) const;

        /**
         * Boolean operator "smaller or equal" for my_strings
         * @param otherMyStr - my_string to be compared with
         * @return - true if this smaller or equal than otherMyStr, false otherwise
         */
        bool operator<= (const big_integer::my_string& otherMyStr) const;

        // ------------------- more operators -------------------

        /**
         * Operator [] - returning the digit of the order "index", example:
         * my_string = "1234567890": my_string[0] = 0; my_string[4] = 6; my_string[9] = 1;
         * @param index - the order of the digit to be returned
         * @return - reference to char representing the index's digit of my_string
         */
        char& operator[] (const int& index) const;

        // ------------------- different helper functions -------------------

        /**
         * Function finds the maximal my_string by absolute value between two my_strings
         * @param other_my_str - the second my_string to be compared with
         * @return my_string that is bigger in absolute value
         */
        my_string maxAbsolute(const my_string &other_my_str) const;

        /**
         * Function finds the minimal my_string by absolute value between two my_strings
         * @param other_my_str - the second my_string to be compared with
         * @return my_string that is smaller in absolute value
         */
        my_string minAbsolute(const my_string &other_my_str) const;

        /**
         * Function creates new my_string representing absolute value of 'this'
         * We don't want to change the original my_string - that's why creating new one
         * @return new my_string representing absolute value of 'this'
         */
        my_string myFabs() const;

        /**
         * Function cleans the zeroes in the beginning of the given my_string, and modify it
         * data members properly
         * @return reference to my_string - the updated 'this' - without zeroes in the beginning
         */
        my_string& cleanZeroes();

        /**
         * Function checks if all the digits of my_string are zeroes or not
         * @return - true if all the digits of my_string are zeroes, false otherwise
         */
        bool onlyZeroes() const;

        /**
         * Functions counts sum of two my_strings and put the result into res_my_str
         * The sum is made by digits - "long sum"
         * @param other_my_str - my_string to be added to 'this'
         * @param res_my_str - resulting my_string representing the sum of 'this' and other
         * @return reference to res_my_str
         */
        my_string& sumMyString(const my_string &other_my_str, my_string &res_my_str) const;

        /**
         * Functions counts subtraction of two my_strings and put the result into res_my_str
         * The subtraction is made by digits - "long subtraction"
         * @param other_my_str - my_string to be subtracted from 'this'
         * @param res_my_str - resulting my_string representing the subtraction of 'this' and other
         * @return reference to res_my_str
         */
        my_string& subtractMyString(const my_string &other_my_str, my_string &res_my_str) const;

        /**
         * Functions counts multiplication of two my_strings and put the result into res_my_str
         * The multiplication is made by multiplication by every digit of the shortest number
         * Them summing up all the results
         * @param other_my_str - my_string to be multiplied on 'this'
         * @param res_my_str resulting my_string representing multiplication of 'this' and other
         * @return reference to res_my_str
         */
        my_string& multiplyMyString(const my_string &other_my_str, my_string &res_my_str) const;

        /**
         * Functions counts multiplication of my_strings by digit and put the result in res_my_str
         * @param digit - integer digit to be multiplied on
         * @param res_my_str resulting my_string representing the multiplication of 'this' by digit
         * @return reference to res_my_str
         */
        my_string& multiplyByDigit(int digit, my_string& res_my_str) const;

        /**
         * Functions counts division of two my_strings and put the result into res_my_str
         * The division is made recursively - "long division". Firstly looking for the smallest
         * left sub-number of the dividend that can be divided by divisor. Then division by looking
         * for digit that satisfy the current numbers. Then cutting of the dividend by used part
         * and recursive call with the same divisor, and updated res_my_str
         * @param other_my_str - my_string representing divisor
         * @param res_my_str resulting my_string representing division of 'this' and divisor
         * @return reference to res_my_str
         */
        my_string& divideMyString(const my_string &divisor_my_str, my_string &res_my_str) const;

        // ------------------- getters -------------------

        /**
         * Getter for _str of my_string @see _str
         * @return _str - of type std::string
         */
        std::string getString() const;

        // ------------------- setters -------------------

        /**
         * Setter for _str of my_string @see _str
         * @param new_str - new string to be set up
         */
        void setStr(std::string& new_str);

        // ------------------- destructor -------------------

        /**
         * The default destructor for my_string cause we have no deep parameters
         */
        ~my_string() = default;

    private:
        std::string _str; /**<_str - contains the number itself without a sign*/
        unsigned long _size; /**<_size - represents number of digits in the number
                            (length of the _str) without a sign*/
        bool _sign; /**<_sign - boolean value that is false if the holden number is negative,
                      true otherwise*/
    };

    my_string _data; /**<_data - private object of type my_string representing big_integer value*/
public:

    // ------------------- constructors -------------------

    /**
     * The default constructor for big_integer
     */
    big_integer() = default;

    /**
     * The copy constructor for big_integers = default - there are no deep data structures
     * @param otherBigInt - object of type big_integer to be copied
     */
    big_integer(const big_integer &otherBigInt) = default; // copy constructor

    /**
     * Constructor for big_integer with integer
     * @param int_value - integer to be passed into big_integer object
     */
    big_integer(long int int_value); // constructor with integer

    /**
     * Constructor for big_integer with string representing big integer number
     * @param str_int - string to be passed into big_integer object
     */
    explicit big_integer(const std::string& str_int); // constructor with string

    // ------------------------------- boolean operators -------------------------------

    /**
     * Boolean comparison operator for big_integers
     * @param otherBigInt - big_integer to be compared with
     * @return - true if this and otherBigInt are equal, false otherwise
     */
    bool operator==(const big_integer& otherBigInt) const;

    /**
     * Boolean not-equal operator for big_integers
     * @param otherBigInt - big_integer to be compared with
     * @return - true if this and otherBigInt are not equal, false otherwise
     */
    bool operator!=(const big_integer& otherBigInt) const;

    /**
     * Boolean operator "smaller" for big_integers
     * @param otherBigInt - big_integer to be compared with
     * @return - true if this smaller then otherBigInt, false otherwise
     */
    bool operator<(const big_integer& otherBigInt) const;

    /**
     * Boolean operator "bigger" for big_integers
     * @param otherBigInt - big_integer to be compared with
     * @return - true if this bigger then otherBigInt, false otherwise
     */
    bool operator>(const big_integer& otherBigInt) const;

    /**
     * Boolean operator "smaller or equal" for big_integers
     * @param otherBigInt - big_integer to be compared with
     * @return - true if this smaller or equal then otherBigInt, false otherwise
     */
    bool operator<= (const big_integer& otherBigInt) const;

    /**
     * Boolean operator "bigger or equal" for big_integers
     * @param otherBigInt - big_integer to be compared with
     * @return - true if this bigger or equal then otherBigInt, false otherwise
     */
    bool operator>= (const big_integer& otherBigInt) const;

    // ------------------------------- arithmetic operators -------------------------------

    /**
     * Operator assignment for big_integers
     * @param otherBigInt - other big_integer to be assigned to
     * @return - reference to the big_integer that was assigned
     */
    big_integer& operator= (const big_integer& otherBigInt);

    /**
     * Operator plus - Sum of two big_integers
     * @param other_big_int - big_integer to be added to 'this'
     * @return new big_integer representing the sum of this and other
     */
    big_integer operator+(const big_integer& other_big_int) const;

    /**
     * Operator plus-equal - assigning to this sum of itself and other
     * @param other_big_int - other_big_int to be added to 'this'
     * @return reference to big_integer - updated big_integer ('this')
     * representing the sum of itself before operation and other big_integer
     */
    big_integer& operator+=(const big_integer& other_big_int);

    /**
     * Operator minus - subtraction of two big_integers
     * @param other_big_int - big_integer to be subtracted from 'this'
     * @return new big_integer representing the subtraction of this and other
     */
    big_integer operator-(const big_integer& other_big_int) const;

    /**
     * Operator minus-equal - assigning to this subtraction of itself and other
     * @param other_big_int - other_big_int to be subtracted from 'this'
     * @return reference to big_integer - updated big_integer ('this')
     * representing the subtraction of itself before operation and other big_integer
     */
    big_integer& operator-=(const big_integer& other_big_int);

    /**
     * Operator multiplication - multiplication of two big_integers
     * @param other_big_int - big_integer to be multiplied on 'this'
     * @return new big_integer representing the multiplication of this and other
     */
    big_integer operator*(const big_integer& other_big_int) const;

    /**
     * Operator miltiply-equal - assigning to this multipication of itself and other
     * @param other_big_int - other_big_int to be multiplied on 'this'
     * @return reference to big_integer - updated big_integer ('this')
     * representing the multiplication of itself before operation and other big_integer
     */
    big_integer& operator*=(const big_integer& other_big_int);

    /**
     * Operator division - division of two big_integers
     * @param other_big_int - big_integer representing divisor
     * @return new big_integer representing the division of this by other
     */
    big_integer operator/(const big_integer& other_big_int) const;

    /**
     * Operator divide-equal - assigning to this division of itself and other
     * @param other_big_int - other_big_int representing divisor
     * @return reference to big_integer - updated big_integer ('this')
     * representing the division of itself before operation by other big_integer
     */
    big_integer& operator/=(const big_integer& other_big_int);

    /**
     * Operator modulus - remainder of division of two big_integers
     * @param other_big_int - big_integer representing divisor
     * @return new big_integer representing the modulus if the division of this by other
     */
    big_integer operator%(const big_integer& other_big_int) const;

    // ------------------------------- more operators -------------------------------

    /**
     * The operator for representing big_integer into stream os, the sign and the number itself
     * @param os - stream for passing the representation into it
     * @param big_int - big_integer to be represented
     * @return reference to the stream that was updated
     */
    friend std::ostream& operator<< (std::ostream& os, const big_integer& big_int);

    // -------------------------------  getters -------------------------------

    /**
     * Getter for _data of big_integer @see _data
     * @return _str - of type std::string representing the big_integer
     */
    std::string getString() const;

    // ------------------------------- destructor -------------------------------

    /**
    * The default destructor for big_integer cause we have no deep parameters
    */
    ~big_integer() = default;
};

#endif //EX1C_BIG_INTEGER_H
