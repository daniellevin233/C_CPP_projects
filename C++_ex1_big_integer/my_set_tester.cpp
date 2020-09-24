/*
 * my_set_tester.cpp
 *
 * Author: Oded Wertheimer
 *
 * All tests are related - if you fail the addition test you will probably fail the next tests as
 * the wrong elements will be in the set.
 * The tests check some edge cases, but there are probably more - please inform me if you notice
 * new edge cases to add to the tester.
 */

#include <iostream>
#include <sstream>
#include "big_integer.h"
#include "my_set.h"

using std::stringstream;
using std::string;


bool testRemove(stringstream &out, my_set &set1)
{//remove tests
    bool successFlag = true;
    big_integer BB(50);
    set1.remove(BB);
//    set1.remove(big_integer(50));
    out << set1;
    if (out.str() != "13\n15\n17\n20\n23\n25\n27\n")
    {
        std::cout << "Test 4.1 failed - expected:\n" << "13\n15\n17\n20\n23\n25\n27\n" << "Yet " \
        "received:\n" << out.str() << std::endl;
        successFlag = false;
    }
    out.str(std::string());

//    set1.remove(big_integer(20));
    big_integer B(20);
    set1.remove(B);
    out << set1;
    if (out.str() != "13\n15\n17\n23\n25\n27\n")
    {
        std::cout << "Test 4.2 failed - expected:\n" << "13\n15\n17\n23\n25\n27\n" << "Yet " \
        "received:\n" << out.str() << std::endl;
        successFlag = false;
    }
    out.str(std::string());
    big_integer A(15);
    set1.remove(A);
//    set1.remove(15);
    out << set1;
    if (out.str() != "13\n17\n23\n25\n27\n")
    {
        std::cout << "Test 4.3 failed - expected:\n" << "13\n17\n23\n25\n27\n" << "Yet " \
        "received:\n" << out.str() << std::endl;
        successFlag = false;
    }
    out.str(std::string());

    big_integer Z(25);
    set1.remove(Z);
//    set1.remove(25);
    out << set1;
    if (out.str() != "13\n17\n23\n27\n")
    {
        std::cout << "Test 4.4 failed - expected:\n" << "13\n17\n23\n27\n" << "Yet " \
        "received:\n" << out.str() << std::endl;
        successFlag = false;
    }
    out.str(std::string());

    big_integer Q(17);
    set1.remove(Q);
//    set1.remove(17);
    out << set1;
    if (out.str() != "13\n23\n27\n")
    {
        std::cout << "Test 4.5 failed - expected:\n" << "13\n23\n27\n" << "Yet " \
        "received:\n" << out.str() << std::endl;
        successFlag = false;
    }
    out.str(std::string());

    big_integer E(27);
    set1.remove(E);
//    set1.remove(27);
    out << set1;
    if (out.str() != "13\n23\n")
    {
        std::cout << "Test 4.6 failed - expected:\n" << "13\n23\n" << "Yet " \
        "received:\n" << out.str() << std::endl;
        successFlag = false;
    }
    out.str(std::string());

    big_integer R(13);
    set1.remove(R);
//    set1.remove(13);
    out << set1;
    if (out.str() != "23\n")
    {
        std::cout << "Test 4.7 failed - expected:\n" << "23\n" << "Yet " \
        "received:\n" << out.str() << std::endl;
        successFlag = false;
    }
    out.str(std::string());

    big_integer W(23);
    set1.remove(W);
//    set1.remove(23);
    out << set1;
    if (out.str() != "\n")
    {
        std::cout << "Test 4.7 failed - expected:\n" << "\n" << "Yet " \
        "received:\n" << out.str() << std::endl;
        successFlag = false;
    }
    out.str(std::string());
    set1.add(big_integer(13));
    set1.add(big_integer(23));

    out.str(std::string()); //clear out
    if (successFlag)
    {
        std::cout << "Test 4 passed - deletion successful" << std::endl;
        return true;
    }
    return false;
}

bool testDuplicates(stringstream &out, my_set &set1)
{//no duplicates test
    set1.add(big_integer(20));
    set1.add(big_integer(15));
    set1.add(big_integer(25));
    set1.add(big_integer(17));
    set1.add(big_integer(27));
    set1.add(big_integer(13));
    set1.add(big_integer(23));

    out << set1;
    if (out.str() == "13\n15\n17\n20\n23\n25\n27\n")
    {
        std::cout << "Test 3 passed - no duplicates were added" << std::endl;
        out.str(std::string()); //clear out
        return true;
    }
    else
    {
        std::cout << "Test 3 failed - expected:\n" << "13\n15\n17\n20\n23\n25\n27\n " << "Yet " \
        "received:\n" << out.str() << std::endl;
        out.str(std::string()); //clear out
        return false;
    }
}

bool testAddition(stringstream &out, my_set &set1)
{//add and prints tests:
    set1.add(big_integer(20));
    set1.add(big_integer(15));
    set1.add(big_integer(25));
    set1.add(big_integer(17));
    set1.add(big_integer(27));
    set1.add(big_integer(13));
    set1.add(big_integer(23));

    out << set1;
    if (out.str() == "13\n15\n17\n20\n23\n25\n27\n")
    {
        std::cout << "Test 2 passed - added all elements and printed in order" << std::endl;
        out.str(std::string()); //clear out
        return true;
    }
    else
    {
        std::cout << "Test 2 failed - expected:\n" << "13\n15\n17\n20\n23\n25\n27\n " << "Yet " \
        "received:\n" << out.str() << std::endl;
        out.str(std::string()); //clear out
        return false;
    }

}

bool testEmptySetPrint(stringstream &out, my_set &set2)
{
    out << set2;
    if (out.str() == "\n")
    {
        std::cout << "Test 1 passed - printing empty set prints newline" << std::endl;
        out.str(string());
        return true;
    }
    else
    {
        std::cout << "Test 1 failed - expected:\n" << "\n" << "Yet " \
        "received:\n" << out.str() << std::endl;
        out.str(string());
        return false;
    }
}

bool testCopyConstructorValues(stringstream &out, const my_set &set1, my_set &set2)
{
    set2 = my_set(set1);
    out << set2;
    if (out.str() == "13\n23\n")
    {
        std::cout << "Test 5 passed - successfully created set from copy constructor" << std::endl;
        out.str(string()); //clear out
        return true;
    }
    else
    {
        std::cout << "Test 5 failed - expected:\n" << "13\n23\n" << "Yet " \
        "received:\n" << out.str() << std::endl;
        out.str(string()); //clear out
        return false;
    }
}

bool testCopyValuesNotPointers(stringstream &out, my_set &set1, my_set &set2)
{
    bool successFlag = true;
    big_integer A(13);
    set2.remove(A);
//    set2.remove(big_integer(13));
    out << set2;
    stringstream out2;
    out2 << set1;
    if (out.str() != "23\n" || out2.str() != "13\n23\n")
    {
        std::cout << "Test 6.1 failed - copy constructor points to old values and does not create "
                "new" << std::endl;
        successFlag = false;
    }
    out.str(std::string());
    set2.remove(big_integer(23));
    out << set2;
    if (out.str() != "\n" || out2.str() != "13\n23\n")
    {
        std::cout << "Test 6.2 failed - copy constructor points to old values and does not create "
                "new" << std::endl;
        successFlag = false;
    }
    out.str(string()); //clear out
    if (successFlag)
    {
        std::cout << "Test 6 passed - copy constructor does not point to old values but creates new"
                  << std::endl;
        return true;
    }
    return false;
}

bool testSum(my_set &set)
{
    int i = 0;
    for (i = 0; i < 30; ++i)
    {
        set.add(big_integer(i));
    }
    if (set.sum_set() == big_integer(435))
    {
        std::cout << "Test 7 passed - summation works as expected" << std::endl;
        return true;
    }
    else
    {
        std::cout << "Test 7 failed - expected: 435, Yet received:\n" << set.sum_set()
                  << std::endl;
        return false;
    }
}

bool TestMinus(stringstream &out, const my_set &smallSet, my_set &largeSet, const my_set &emptySet)
{
    bool successFlag = true;
    out << (largeSet - emptySet);
    stringstream expected;
    expected << largeSet;
    if (out.str() != expected.str())
    {
        std::cout << "Test 8.1 failed - expected:\n" << expected.str() << "\nYet received:\n" <<
                  out.str() << std::endl;
        successFlag = false;
    }
    out.str(string());
    expected.str(string());
    out << (largeSet - smallSet);
    if (out.str() != "0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n14\n15\n16\n17\n18\n19\n20\n21\n22"
            "\n24\n25\n26\n27\n28\n29\n")
    {
        std::cout << "Test 8.2 failed - expected:\n"
                  << "0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n14\n15\n16\n17\n18\n19\n20\n21\n22"
                          "\n24\n25\n26\n27\n28\n29\n" << "\nYet received:\n" <<
                  out.str() << std::endl;
        successFlag = false;
    }
    out.str(string());

    out << (largeSet - largeSet);
    if (out.str() != "\n")
    {
        std::cout << "Test 8.3 failed - expected:\n:" << "\n" << "\nYet received:\n" << out.str()
                  << std::endl;
        successFlag = false;
    }
    out.str(string());
    if (successFlag)
    {
        std::cout << "Test 8 passed - deducting sets from one another successful" << std::endl;
        return true;
    }
    return false;
}

bool testUniteOperator(stringstream &out, my_set &set1, my_set &set2, my_set &set3, my_set &set4)
{// The sets should be:
// set1 - 13\n23\n
// set2 - empty
// set3 - 0 to 29
// set4 - 30 to 35
    bool successFlag = true;
    out << (set1 | set4); //should add
    if (out.str() != "13\n23\n30\n31\n32\n33\n34\n35\n")
    {
        std::cout << "Test 9.1 failed - expected:\n" << "13\n23\n30\n31\n32\n33\n34\n35\n"
                  << "\nYet received:\n" << out.str() << std::endl;
        successFlag = false;
    }
    out.str(string());

    out << (set1 | set2); //should stay the same
    if (out.str() != "13\n23\n")
    {
        std::cout << "Test 9.2 failed - expected:\n" << "13\n23\n"
                  << "\nYet received:\n" << out.str() << std::endl;
        successFlag = false;
    }
    out.str(string());

    out << (set2 | set4); //should add
    if (out.str() != "30\n31\n32\n33\n34\n35\n")
    {
        std::cout << "Test 9.3 failed - expected:\n" << "30\n31\n32\n33\n34\n35\n"
                  << "\nYet received:\n" << out.str() << std::endl;
        successFlag = false;
    }
    out.str(string());

    out << (set3 | set4); //should add
    if (out.str() != "0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20"
            "\n21\n22\n23\n24\n25\n26\n27\n28\n29\n30\n31\n32\n33\n34\n35\n")
    {
        std::cout << "Test 9.4 failed - expected: 0 to 35 (inclusive), Yet received:\n" << out.str()
                  << std::endl;
        successFlag = false;
    }
    out.str(string());

    out << (set3 | set1); //should stay the same
    if (out.str() != "0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20"
            "\n21\n22\n23\n24\n25\n26\n27\n28\n29\n")
    {
        std::cout << "Test 9.5 failed - expected: 0 to 29 (inclusive), Yet received:\n" << out.str()
                  << std::endl;
        successFlag = false;
    }
    out.str(string());
    if (successFlag)
    {
        std::cout << "Test 9 passed - | operator works as expected" << std::endl;
        return true;
    }
    return false;
}

void initSet4(my_set &set4)
{
    int i;
    for (i = 30; i <= 35; ++i)
    {
        set4.add(big_integer(i));
    }
}

bool testAndOperator(stringstream &out, my_set &set1, my_set &set2, my_set &set3,
                     const my_set &set4)
{
    bool successFlag = true;
    out << (set1 & set2); //set & empty set
    if (out.str() != "\n")
    {
        std::cout << "Test 10.1 failed - expected newline, Yet received:\n" << out.str() <<
                  std::endl;
        successFlag = false;
    }
    out.str(string());

    out << (set2 & set3); //empty set & set
    if (out.str() != "\n")
    {
        std::cout << "Test 10.2 failed - expected newline, Yet received:\n" << out.str() <<
                  std::endl;
        successFlag = false;
    }
    out.str(string());

    out << (set1 & set3); // set&set with shared elements
    if (out.str() != "13\n23\n")
    {
        std::cout << "Test 10.3 failed - expected:\n13\n23\n\nYet received:\n" << out.str() <<
                  std::endl;
        successFlag = false;
    }
    out.str(string());

    out << (set3 & set4); // set&set without shared elements
    if (out.str() != "\n")
    {
        std::cout << "Test 10.4 failed - expected newline, Yet received:\n" << out.str() <<
                  std::endl;
        successFlag = false;
    }
    out.str(string());
    if (successFlag)
    {
        std::cout << "Test 10 passed - & operator works as expected" << std::endl;
        return true;
    }
    return false;
}

/**
 * Main - entry point for tester.
 */
int main()
{
    bool allTestsPassed = true;
    stringstream out;
    my_set set1, set2, set3, set4;

    allTestsPassed = allTestsPassed && testEmptySetPrint(out, set2); //1
    allTestsPassed = allTestsPassed && testAddition(out, set1); //2
    allTestsPassed = allTestsPassed && testDuplicates(out, set1); //3
    allTestsPassed = allTestsPassed && testRemove(out, set1); //4
    allTestsPassed = allTestsPassed && testCopyConstructorValues(out, set1, set2); //5
    allTestsPassed = allTestsPassed && testCopyValuesNotPointers(out, set1, set2); //6
    allTestsPassed = allTestsPassed && testSum(set3); //7
    allTestsPassed = allTestsPassed && TestMinus(out, set1, set3, set2);//8
    initSet4(set4);
    allTestsPassed = allTestsPassed && testUniteOperator(out, set1, set2, set3, set4); //9
    allTestsPassed = allTestsPassed && testAndOperator(out, set1, set2, set3, set4); //10
    std::cout << "------------------------------------------------" << std::endl;
    if (allTestsPassed)
    {
        std::cout << "All tests Passed!" << std::endl;
    }
    else
    {
        std::cout << "You failed some of the tests" << std::endl;
    }
    return 0;
}




