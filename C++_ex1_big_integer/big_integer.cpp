// big_integer.cpp

//libraries imports
#include <iostream>
#include "big_integer.h"
#include "my_set.h"
#include <cmath>

//some useful std objects
using std::ostream;
using std::cout;
using std::endl;
using std::string;
using std::to_string;

// --------------------------------------------------------------------------------------
// This file contains the implementation of the class big_integer.
// --------------------------------------------------------------------------------------

/**
 * Constructor for big_integer with integer
 * @param int_value - long integer to be passed to big_integer
 */
big_integer::big_integer(const long int int_value)
:_data(to_string(int_value))
{}

//ctor for big_integer with string
big_integer::big_integer(const string& str_int)
{
    unsigned long size = str_int.length();
    if(!str_int.length() || (str_int[0] != NEGATIVE_CHAR && !isdigit(str_int[0])) ||
       (str_int == NULL_STR) || (str_int == NEGATIVE_STR))
    {
        _data = my_string();
        return;
    }
    for(string::size_type i = 1; i < size; ++i)
    {
        if(!std::isdigit(str_int[i]))
        {
            _data = my_string();
            return;
        }
    }
    _data = my_string(str_int).cleanZeroes(); // throw redundant zeroes out
}

/**
 * The default constructor for my_string that doesn't get anything and set my_string to "0"
 */
big_integer::my_string::my_string() // default ctor for string
: _str(NULL_STR), _size(1), _sign(true)
{}

/**
 * Constructor for my_string with string (std)
 * @param std_str - standard string to be passed into my_string object
 */
big_integer::my_string::my_string(const string& std_str)// ctor for string with string
{
    _str = std_str;
    _size = std_str.length();
    _sign = (_str[0] != NEGATIVE_CHAR);
    if(!_sign)
    {
        _str = _str.substr(1, _size - 1);
        _size -= 1;
    }
}

/**
 * Constructor for my_string with string (std)
 * @param std_str - standard string to be passed into my_string object
 */
big_integer::my_string::my_string(const string& std_str, bool& sign)
// ctor for my_string with string without a sign and boolean
:_str(std_str), _size(std_str.length()), _sign(sign) {}

/**
 * Operator assignment for my_strings
 * @param myStrRhs - other my_string to be assigned to
 * @return - reference to the my_string that was assigned
 */
big_integer::my_string& big_integer::my_string::operator=(const big_integer::my_string& myStrRhs)
{
    if(this != &myStrRhs)
    {
        _str = myStrRhs._str;
        _size = myStrRhs._size;
        _sign = myStrRhs._sign;
    }
    return *this;
}

/**
 * Getter for _str of my_string @see _str
 * @return _str - of type std::string
 */
string big_integer::my_string::getString() const
{
    return ((_str == NULL_STR || _sign) ? _str : (NEGATIVE_STR + _str));
}

/**
 * Setter for _str of my_string @see _str
 * @param new_str - new string to be set up
 */
void big_integer::my_string::setStr(string& new_str)
{
    _str = new_str;
    _size = new_str.length();
}

/**
 * Getter for _data of big_integer @see _data
 * @return _str - of type std::string representing the big_integer
 */
string big_integer::getString() const
{
    return _data.getString();
}

/**
 * The operator for representing big_integer into stream os, the sign and the number itself
 * @param os - stream for passing the representation into it
 * @param big_int - big_integer to be represented
 * @return reference to the stream that was updated
 */
ostream& operator<< (ostream &os, const big_integer& bigInt)
{
    return (os << bigInt.getString());
}

/**
 * Operator assignment for big_integers
 * @param otherBigInt - other big_integer to be assigned to
 * @return - reference to the big_integer that was assigned
 */
big_integer& big_integer::operator=(const big_integer& bigIntRhc)
{
    if(this != &bigIntRhc)
    {
        _data = bigIntRhc._data;
    }
    return *this;
}

/**
 * Operator [] - returning the digit of the order "index", example:
 * my_string = "1234567890": my_string[0] = 0; my_string[4] = 6; my_string[9] = 1;
 * @param index - the order of the digit to be returned
 * @return - reference to char representing the index's digit of my_string
 */
char& big_integer::my_string::operator[](const int& index) const
{
    return const_cast<char&>(_str[_size - index - 1]);
}

/**
 * Boolean comparison operator for my_strings
 * @param otherMyStr - my_string to be compared with
 * @return - true if this and otherMyStr are equal, false otherwise
 */
bool big_integer::my_string::operator==(const big_integer::my_string& otherMyStr) const
{
    return ((_str == NULL_STR) && (otherMyStr._str == NULL_STR)) ? true :
           ((_sign == otherMyStr._sign) && (_str == otherMyStr._str));
}

/**
 * Boolean operator "smaller" for my_strings
 * @param otherMyStr - my_string to be compared with
 * @return - true if this smaller than otherMyStr, false otherwise
 */
bool big_integer::my_string::operator<(const big_integer::my_string& otherMyStr) const
{
    if((_sign != otherMyStr._sign)) // the integers are of different signs
    {
        return !_sign; // if sign is negative, it's smaller - return true, otherwise return false
    }
    else if(this->_size != otherMyStr._size) // one string is longer than another
    {
        return (this->_size < otherMyStr._size);
    }
    else
    {
        return (_str < otherMyStr._str);
    }
}

/**
 * Boolean operator "smaller or equal" for my_strings
 * @param otherMyStr - my_string to be compared with
 * @return - true if this smaller or equal than otherMyStr, false otherwise
 */
bool big_integer::my_string::operator<=(const big_integer::my_string& otherMyStr) const
{
    return (*this < otherMyStr) || (*this == otherMyStr);
}

/**
 * Boolean not-equal operator for big_integers
 * @param otherBigInt - big_integer to be compared with
 * @return - true if this and otherBigInt are not equal, false otherwise
 */
bool big_integer::operator!=(const big_integer& otherBigInt) const
{
    return !(_data == otherBigInt._data);
}

/**
 * Boolean comparison operator for big_integers
 * @param otherBigInt - big_integer to be compared with
 * @return - true if this and otherBigInt are equal, false otherwise
 */
bool big_integer::operator==(const big_integer& otherBigInt) const
{
    return (_data == otherBigInt._data);
}

/**
 * Boolean operator "smaller" for big_integers
 * @param otherBigInt - big_integer to be compared with
 * @return - true if this smaller then otherBigInt, false otherwise
 */
bool big_integer::operator<(const big_integer& otherBigInt) const
{
    return (_data < otherBigInt._data);
}

/**
 * Boolean operator "bigger" for big_integers
 * @param otherBigInt - big_integer to be compared with
 * @return - true if this bigger then otherBigInt, false otherwise
 */
bool big_integer::operator>(const big_integer& otherBigInt) const
{
    return !(_data <= otherBigInt._data);
}

/**
 * Boolean operator "smaller or equal" for big_integers
 * @param otherBigInt - big_integer to be compared with
 * @return - true if this smaller or equal then otherBigInt, false otherwise
 */
bool big_integer::operator<=(const big_integer& otherBigInt) const
{
    return (_data <= otherBigInt._data);
}

/**
 * Boolean operator "bigger or equal" for big_integers
 * @param otherBigInt - big_integer to be compared with
 * @return - true if this bigger or equal then otherBigInt, false otherwise
 */
bool big_integer::operator>=(const big_integer& otherBigInt) const
{
    return (!(_data < otherBigInt._data));
}

/**
 * Function creates new my_string representing absolute value of 'this'
 * We don't want to change the original my_string - that's why creating new one
 * @return new my_string representing absolute value of 'this'
 */
big_integer::my_string big_integer::my_string::myFabs() const
{
    my_string fabs_my_str = *this;
    fabs_my_str._sign = true;
    return fabs_my_str;
}

/**
 * Function finds the maximal my_string by absolute value between two my_strings
 * @param other_my_str - the second my_string to be compared with
 * @return my_string that is bigger in absolute value
 */
big_integer::my_string big_integer::my_string::maxAbsolute(const big_integer::my_string &other_my_str) const
{
    return ((myFabs() < other_my_str.myFabs()) ? other_my_str : (*this));
}

/**
 * Function finds the minimal my_string by absolute value between two my_strings
 * @param other_my_str - the second my_string to be compared with
 * @return my_string that is smaller in absolute value
 */
big_integer::my_string big_integer::my_string::minAbsolute(const big_integer::my_string &other_my_str) const
{
    return ((myFabs() < other_my_str.myFabs()) ? (*this) : other_my_str);
}

/**
 * Function cleans the zeroes in the beginning of the given my_string, and modify it
 * data members properly
 * @return reference to my_string - the updated 'this' - without zeroes in the beginning
 */
big_integer::my_string& big_integer::my_string::cleanZeroes()
{
    unsigned long i = 0;
    while(_str[i] == NULL_CHAR && i < (_size - 1))
    {
        ++i;
    }
    string new_str = _str.substr(i, _size - i); // concatenating the new string
    this->setStr(new_str);
    return *this;
}

/**
 * Functions counts sum of two my_strings and put the result into res_my_str
 * The sum is made by digits - "long sum"
 * @param other_my_str - my_string to be added to 'this'
 * @param res_my_str - resulting my_string representing the sum of 'this' and other
 * @return reference to res_my_str
 */
big_integer::my_string& big_integer::my_string::sumMyString(const big_integer::my_string &other_my_str,
       big_integer::my_string &res_my_str) const
{
    string res_str;
    int additional_value = 0, cur_digit; // additional value represents passing value for digits
    my_string short_str = minAbsolute(other_my_str);
    my_string long_str = maxAbsolute(other_my_str);
    unsigned int i;
    for(i = 0; i < short_str._size; ++i) // for loop onto the shortest number
    {
        cur_digit = ((*this)[i] - NULL_CHAR) + (other_my_str[i] - NULL_CHAR) + additional_value;
        res_str = to_string(cur_digit % TENS_VALUE).append(res_str);
        additional_value = (cur_digit >= TENS_VALUE) ? 1 : 0;
    }
    for(; i < long_str._size; ++i) // for loop onto the longest number
    {
        cur_digit = long_str[i] - NULL_CHAR + additional_value;
        res_str = to_string(cur_digit % TENS_VALUE).append(res_str);
        additional_value = (cur_digit >= TENS_VALUE) ? 1 : 0;
    }
    if(additional_value)
    {
        res_str = to_string(additional_value).append(res_str);
    }
    res_my_str.setStr(res_str);
    return res_my_str.cleanZeroes();
}
/**
 * Functions counts subtraction of two my_strings and put the result into res_my_str
 * The subtraction is made by digits - "long subtraction"
 * @param other_my_str - my_string to be subtracted from 'this'
 * @param res_my_str - resulting my_string representing the subtraction of 'this' and other
 * @return reference to res_my_str
 */
big_integer::my_string& big_integer::my_string::subtractMyString(const big_integer::my_string &other_my_str,
                                                                 big_integer::my_string &res_my_str) const
{
    string res_str;
    int reduce_value = 0, cur_digit;
    my_string short_str = minAbsolute(other_my_str);
    my_string long_str = maxAbsolute(other_my_str);
    unsigned int i;
    for(i = 0; i < short_str._size; ++i) // for loop onto the shortest number
    {
        cur_digit = (long_str[i] - NULL_CHAR - reduce_value) - (short_str[i] - NULL_CHAR);
        if(cur_digit < 0)
        {
            cur_digit += TENS_VALUE;
            reduce_value = 1;
        }
        else
        {
            reduce_value = 0;
        }
        res_str = to_string(cur_digit).append(res_str);
    }
    for(; i < long_str._size; ++i) // for loop onto the longest number
    {
        cur_digit = long_str[i] - NULL_CHAR - reduce_value;
        reduce_value = (cur_digit >= 0) ? 0 : 1;
        res_str = to_string((cur_digit + TENS_VALUE) % TENS_VALUE).append(res_str);
    }
    res_my_str.setStr(res_str);
    return res_my_str.cleanZeroes();
}

/**
 * Functions counts multiplication of my_strings by digit and put the result in res_my_str
 * @param digit - integer digit to be multiplied on
 * @param res_my_str resulting my_string representing the multiplication of 'this' by digit
 * @return reference to res_my_str
 */
big_integer::my_string&
big_integer::my_string::multiplyByDigit(const int digit, big_integer::my_string& res_my_str) const
{
    string res_str;
    unsigned int additional_value = 0, cur_digit;
    for(unsigned int i = 0; i < _size; ++i)
    {
        cur_digit = ((*this)[i] - NULL_CHAR) * digit + additional_value;
        res_str = to_string(cur_digit % TENS_VALUE).append(res_str);
        additional_value = cur_digit / TENS_VALUE;
    }
    res_my_str.setStr(to_string(additional_value).append(res_str));
    return res_my_str.cleanZeroes();
}

/**
 * Functions counts multiplication of two my_strings and put the result into res_my_str
 * The multiplication is made by multiplication by every digit of the shortest number
 * Them summing up all the results
 * @param other_my_str - my_string to be multiplied on 'this'
 * @param res_my_str resulting my_string representing multiplication of 'this' and other
 * @return reference to res_my_str
 */
big_integer::my_string&
big_integer::my_string::multiplyMyString(const big_integer::my_string &other_my_str,
       big_integer::my_string &res_my_str) const
{
    string res_str;
    my_string short_str = minAbsolute(other_my_str);
    my_string long_str = maxAbsolute(other_my_str);
    unsigned long i;
    my_string cur_my_str;
    for(i = 0; i < short_str._size; ++i)
    {
        cur_my_str = long_str.multiplyByDigit(short_str[i] - NULL_CHAR, cur_my_str);
        cur_my_str.setStr(cur_my_str._str.append(string(i, NULL_CHAR)));
        res_my_str += cur_my_str;
    }
    return res_my_str;
}

/**
 * Function checks if all the digits of my_string are zeroes or not
 * @return - true if all the digits of my_string are zeroes, false otherwise
 */
bool big_integer::my_string::onlyZeroes() const
{
    for(unsigned int i = 0; i < _size; ++i)
    {
        if((*this)[i] != NULL_CHAR)
        {
            return false;
        }
    }
    return true;
}

/**
 * Functions counts division of two my_strings and put the result into res_my_str
 * The division is made recursively - "long division". Firstly looking for the smallest
 * left sub-number of the dividend that can be divided by divisor. Then division by looking
 * for digit that satisfy the current numbers. Then cutting of the dividend by used part
 * and recursive call with the same divisor, and updated res_my_str;
 * see the internal comments for better understanding
 * @param other_my_str - my_string representing divisor
 * @param res_my_str resulting my_string representing division of 'this' and divisor
 * @return reference to res_my_str
 */
big_integer::my_string&
big_integer::my_string::divideMyString(const big_integer::my_string &divisor_my_str,
       big_integer::my_string &res_my_str) const
{
    if(this->onlyZeroes() && (_str != NULL_STR))
        // only zeroes in the end of the number reminding - add it to result
    {
        string new_res_str = res_my_str._str + string(_size - 1, NULL_CHAR);
        res_my_str.setStr(new_res_str);
        return res_my_str.cleanZeroes();
    }
    else if ((*this < divisor_my_str) || (divisor_my_str._str == NULL_STR))
    // the base recursion case, the reminding dividend is smaller than divisor or division by zero
    {
        return res_my_str.cleanZeroes();
    }
    string res_str;
    unsigned long i = 1;
    my_string cur_str, my_str_helper, cur_multiply_res, reminder, reminding_part; // helpers!!!
    // PS: created for readability (if it exists at all)
    do // firstly we want to find the minimal beginning part of the dividend that can be
        // divided by divisor
    {
        cur_str = my_string(_str.substr(0, i));
        ++i;
    }while((cur_str.cleanZeroes() < divisor_my_str) && i <= _size);
    int next_digit;
    for(next_digit = 0; next_digit < TENS_VALUE; ++next_digit)
        // here we are looking for the digit that will be the next digit in the answer
    {
        my_str_helper = my_string(to_string(next_digit + 1));
        // the candidate for the next digit in the answer number
        cur_multiply_res = divisor_my_str * my_str_helper;
        // the value representing multiplication of divisor and candidate for the next digit
        if(cur_str < cur_multiply_res)
        {
            res_str += to_string(next_digit);
            break;
        }
    }
    res_my_str.setStr(res_my_str._str.append(res_str)); // the whole resulting string
    reminding_part = cur_str - (my_string(to_string(next_digit)) * divisor_my_str);
    // the part that was divided minus the whole part of the dividing that we've got
    string new_reminder_str = reminding_part._str + _str.substr(i - 1, _size - (i - 1));
    reminder.setStr(new_reminder_str);
    int k = 0;
    while(reminding_part < reminder)
    {
        reminding_part.setStr(reminding_part._str.append(to_string(_str[cur_str._size + k]
                                                                   - NULL_CHAR)));
        ++k;
        if(reminding_part < divisor_my_str)
        {
            res_my_str.setStr(res_my_str._str.append(NULL_STR));
        }
    }
    // it is basically long division we are leaving the part that was divided minus the whole
    // part, and concatenating the right part of the dividend that we haven't touched yet
    return reminder.divideMyString(divisor_my_str, res_my_str);
}

/**
 * Operator plus - Sum of two my_strings
 * @param other_my_str - my_string to be added to 'this'
 * @return new my_string representing the sum of this and other
 */
big_integer::my_string big_integer::my_string::operator+ (const my_string& other_my_str) const
{
    my_string res_sum;
    if(_sign == other_my_str._sign) //the same signs
    {
        res_sum = sumMyString(other_my_str, res_sum);
        res_sum._sign = _sign;
    }
    else // the signs are different
    {
        res_sum = subtractMyString(other_my_str, res_sum);
        res_sum._sign = maxAbsolute(other_my_str)._sign; // if the signs are different -
        // the biggest absolute value's sign wins
    }
    return res_sum;
}

/**
 * Operator plus-equal - assigning to this sum of itself and other
 * @param other_my_str - my_string to be added to 'this'
 * @return reference to my_string - updated my_string ('this')
 * representing the sum of itself before operation and other my_string
 */
big_integer::my_string& big_integer::my_string::operator+= (const my_string& other_my_str)
{
    *this = *this + other_my_str;
    return *this;
}

/**
 * Operator minus - difference between two my_strings
 * @param other_my_str - my_string to be subtracted from 'this'
 * @return new my_string representing the difference of this and other
 */
big_integer::my_string big_integer::my_string::operator- (const my_string& other_my_str) const
{
    my_string neg_my_str = other_my_str;
    neg_my_str._sign = !other_my_str._sign;
    return (*this + neg_my_str);
}

/**
 * Operator multiplication - multiplication of two my_strings
 * @param other_my_str - my_string to be multiplied on 'this'
 * @return new my_string - representing multiplication of 'this' and other
 */
big_integer::my_string big_integer::my_string::operator* (const my_string& other_my_str) const
{
    my_string res_multy;
    res_multy = multiplyMyString(other_my_str, res_multy);
    res_multy._sign = (_sign == other_my_str._sign);
    return res_multy;
}

/**
 * Operator division - division of two my_strings - without remainder (like integers)
 * @param other_my_str - my_string that divides 'this' my_string
 * @return new my_string - representing division of 'this' by other
 */
big_integer::my_string
big_integer::my_string::operator/ (const big_integer::my_string& other_my_str) const
{
    my_string res_division;
    res_division = (myFabs()).divideMyString(other_my_str.myFabs(), res_division);
    res_division._sign = (_sign == other_my_str._sign);
    return res_division.cleanZeroes();
}

/**
 * Operator plus - Sum of two big_integers
 * @param other_big_int - big_integer to be added to 'this'
 * @return new big_integer representing the sum of this and other
 */
big_integer big_integer::operator+ (const big_integer &other_big_int) const
{
    big_integer resInt;
    resInt._data = _data + other_big_int._data;
    return resInt;
}

/**
 * Operator plus-equal - assigning to this sum of itself and other
 * @param other_big_int - other_big_int to be added to 'this'
 * @return reference to big_integer - updated big_integer ('this')
 * representing the sum of itself before operation and other big_integer
 */
big_integer& big_integer::operator+= (const big_integer &other_big_int)
{
    *this = *this + other_big_int;
    return *this;
}

/**
 * Operator minus - subtraction of two big_integers
 * @param other_big_int - big_integer to be subtracted from 'this'
 * @return new big_integer representing the subtraction of this and other
 */
big_integer big_integer::operator-(const big_integer &other_big_int) const
{
    big_integer resInt;
    resInt._data = _data - other_big_int._data;
    return resInt;
}

/**
 * Operator minus-equal - assigning to this subtraction of itself and other
 * @param other_big_int - other_big_int to be subtracted from 'this'
 * @return reference to big_integer - updated big_integer ('this')
 * representing the subtraction of itself before operation and other big_integer
 */
big_integer& big_integer::operator-= (const big_integer &other_big_int)
{
    *this = *this - other_big_int;
    return *this;
}

/**
 * Operator multiplication - multiplication of two big_integers
 * @param other_big_int - big_integer to be multiplied on 'this'
 * @return new big_integer representing the multiplication of this and other
 */
big_integer big_integer::operator* (const big_integer &other_big_int) const
{
    big_integer resInt;
    resInt._data = _data * other_big_int._data;
    return resInt;
}

/**
 * Operator miltiply-equal - assigning to this multipication of itself and other
 * @param other_big_int - other_big_int to be multiplied on 'this'
 * @return reference to big_integer - updated big_integer ('this')
 * representing the multiplication of itself before operation and other big_integer
 */
big_integer& big_integer::operator*= (const big_integer& other_big_int)
{
    *this = (*this) * other_big_int;
    return *this;
}

/**
 * Operator division - division of two big_integers
 * @param other_big_int - big_integer representing divisor
 * @return new big_integer representing the division of this by other
 */
big_integer big_integer::operator/ (const big_integer &other_big_int) const
{
    big_integer resInt;
    resInt._data = _data / other_big_int._data;
    return resInt;
}

/**
 * Operator divide-equal - assigning to this division of itself and other
 * @param other_big_int - other_big_int representing divisor
 * @return reference to big_integer - updated big_integer ('this')
 * representing the division of itself before operation by other big_integer
 */
big_integer& big_integer::operator/= (const big_integer& other_big_int)
{
    *this = (*this) / other_big_int;
    return *this;
}

/**
 * Operator modulus - remainder of division of 'this' by other
 * @param other_my_str - my_string that divides 'this' my_string
 * @return new my_string - representing remainder of division of 'this' by other (modulus)
 */
big_integer::my_string
big_integer::my_string::operator% (const big_integer::my_string& other_my_str) const
{
    my_string res_modulus;
    if(other_my_str._str != NULL_STR)
    {
        res_modulus = (*this) - (other_my_str * ((*this) / other_my_str));
        res_modulus._sign = (res_modulus._str == NULL_STR) ? true : _sign;
    }
    return res_modulus;
}

/**
 * Operator modulus - remainder of division of two big_integers
 * @param other_big_int - big_integer representing divisor
 * @return new big_integer representing the modulus if the division of this by other
 */
big_integer big_integer::operator% (const big_integer& other_big_int) const
{
    big_integer resInt;
    resInt._data = _data % other_big_int._data;
    return resInt;
}