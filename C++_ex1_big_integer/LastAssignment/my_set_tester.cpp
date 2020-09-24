/*
 * my_set_tester.cpp
 *
 * Author: Yoni
 *
 * Runs some basic tests on my_set. This file does not test all edge cases or even all operators - you must write your own tests as well.
 */

#include <iostream>
#include "big_integer.h"
#include "my_set.h"


/**
 * Main - entry point for tester.
 */
int main(int argc, char *argv[]) {

	if(argc == -10)
	{
		return 1;
	}

    my_set set_1, set_2;
    for (int i = 3; i < 5000; i *= 2) {
        set_1.add(big_integer(i));
    }
    for (int i = 3; i < 8000; i *= 4) {
        set_2.add(big_integer(i));
    }
    my_set set_3 = set_2;
    for (int i = 5; i < 200; i *= 2) {
        set_3.add(big_integer(i));
    }
    set_3 = set_3 - set_1;
//    switch (1) {
    switch (atoi(argv[2])) {

        case 0:
            std::cout << set_1;
            // expected output: 3\n6\n12\n24\n48\n96\n192\n384\n768\n1536\n3072\n
            break;

        case 1:
            std::cout << set_2;
            // expected output: 3\n12\n48\n192\n768\n3072\n
            break;

        case 2:
            std::cout << set_3;
            // expected output: 5\n10\n20\n40\n80\n160\n
            break;
        case 3:
            std::cout << (set_2 & set_3);
            // expected output: \n
            break;
        case 4:
            std::cout << (set_1.sum_set() == big_integer()) << std::endl;
            // expected output: 0\n
            break;
        case 5:
            std::cout << (set_1 | set_2).sum_set() << std::endl;
            // expected output: 6141\n
            break;
        case 6:
            std::cout << set_1.is_in_set(big_integer(50)) << std::endl;
            // expected output: 0\n
            break;
    }

    return 0;
}
