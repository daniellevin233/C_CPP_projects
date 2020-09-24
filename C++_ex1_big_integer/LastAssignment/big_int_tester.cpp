/*
 * big_int_tester.cpp
 *
 * Author: Yoni Sher
 *
 * Runs some basic tests on big_integer. This file does not test all edge cases or even all operators - you must write your own tests as well.
 */

#include <iostream>
#include "big_integer.h"

/**
 * Main - entry point for tester.
 */
int main(int argc, char *argv[])
{

	if(argc == -10)
	{
		return 1;
	}

	big_integer big_int_1, big_int_2(5), big_int_3("12345678987654321"), big_int_4;

//    switch(1) {
    switch (atoi(argv[2])) {
        case 0:
            std::cout << big_int_1 << "\n" << big_int_2 << "\n" << big_int_3 << std::endl;
            //expected output: 0\n5\n12345678987654321\n
            break;

        case 1:
            big_int_4 = big_int_2 + big_int_3;
            big_int_2 *= big_integer("10000000000");
            std::cout << big_int_4 << "\n" << big_int_2 << std::endl;
            //expected output: 12345678987654326\n50000000000\n
            break;

        case 2:
            std::cout << (big_int_3 % 2 == 0) << std::endl;
            //expected output: 1\n
            break;

        case 3:
            std::cout << (big_int_2 / 0) << std::endl;
            //expected output: 0\n
            break;

        case 4:
            std::cout << (big_int_2 - big_integer(10)) << std::endl;
            //expected output: -5\n
            break;
            
        case 5:
            std::cout << (big_integer(5) != big_integer(2) + big_integer(3)) << std::endl;
            //expected output: 0\n
            break;
    }
	return 0;
}

