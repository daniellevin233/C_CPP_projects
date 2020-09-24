//
// Created by Nadav Goshen on 26/08/2018.
//

#include <iostream>
#include <string>
#include "big_integer.h"
#include "my_set.h"

using namespace std;

int num = 1;
string numStr = "1";
bool passedAllTests;

big_integer biDEF;
big_integer biINT (num);
big_integer biSTR (numStr);
big_integer biCOPY (biSTR);

void reConstruct()
{
    cout << "\n!-!-! SET NEW BIG_INTEGER OBJECTS !-!-!\n";
    big_integer tempIntBI (num);
    big_integer tempStrBI (numStr);

    biINT = tempIntBI;
    biSTR = tempStrBI;
}

void setTestValues(const int &currNum, const string &currNumStr)
{
    cout << "\n!-!-! SET NEW NUMBER VALUES !-!-!\n";
    num = currNum;
    numStr = currNumStr;
}


void setAdvancedTestValues(const string &currNumStr1, const string &currNumStr2)
{
    big_integer tempStrBI1 (currNumStr1);
    big_integer tempStrBI2 (currNumStr2);
    biINT = tempStrBI1;
    biSTR = tempStrBI2;
}


void printTrivialConstructionReport()
{
    cout      << "\n+++++ TRIVIAL CONSTRUCTION REPORT +++++\n" << endl;

    std::cout << "|| DEF CONST ||" << "\n"
              << "THE NUMBER_STR IS: " << biDEF << "\n"
              << "THE NUMBER_STR SHOULD BE: 0 \n"
              << "----------------------------------------------------------------\n" << endl;

    std::cout << "|| COPY CONST ||" << "\n"
              << "THE NUMBER_STR IS: " << biCOPY << "\n"
              << "THE NUMBER_STR SHOULD BE: 1 \n"
              << "----------------------------------------------------------------\n" << endl;
}


void printSetConstructionReport()
{
    cout      << "\n+++++ SET CONSTRUCTION REPORT +++++\n" << endl;

    std::cout << "|| DEF CONST ||" << "\n"
              << "THE NUMBER_STR IS: " << biDEF << "\n"
              << "THE NUMBER_STR SHOULD BE: 0 \n"
              << "----------------------------------------------------------------\n" << endl;

    std::cout << "|| COPY CONST ||" << "\n"
              << "THE NUMBER_STR IS: " << biCOPY << "\n"
              << "THE NUMBER_STR SHOULD BE: 1 \n"
              << "----------------------------------------------------------------\n" << endl;
}


void printConstructionReport()
{
    cout      << "\n++++++++++++++++++++ CONSTRUCTION REPORT ++++++++++++++++++++\n" << endl;

    std::cout << "|| INT CONST ||" << "\n"
              << "THE NUMBER_STR IS: " << biINT << "\n"
              << "----------------------------------------------------------------\n" << endl;

    std::cout << "|| STRING CONST ||" << "\n"
              << "THE NUMBER_STR IS: " << biSTR << "\n"
              << "----------------------------------------------------------------\n" << endl;
}


void printComparisonReport(const bool &isEqualShouldBe, const bool &isNotEqualShouldBe,
        const bool &isBiggerOrEqualShouldBe, const bool &isSmallerOrEqualShouldBe,
        const bool &isSmallerShouldBe, const bool &isBiggerShouldBe)
{
    bool res;
    res = (biINT == biSTR);

    cout      << "\n+++++++++++++++++++++ COMPARISON REPORT +++++++++++++++++++++\n" << endl;

    std::cout << "|| Are big_integers EQUAL? ||" << "\n"
              << "COMPARISON RESULT IS: " << res << "\n"
              << "COMPARISON RESULT SHOULD BE: " << isEqualShouldBe << "\n\n";
    if (res == isEqualShouldBe) { std::cout << "TEST SUCCESSFULLY PASSED\n" << endl; }
    else
    {
        passedAllTests = false;
        std::cout << "TEST FAILED\n" << endl;
    }

    std::cout << "----------------------------------------------------------------\n" << endl;

    res = (biINT != biSTR);

    std::cout << "|| Are big_integers NOT EQUAL? ||" << "\n"
              << "COMPARISON RESULT IS: " << res << "\n"
              << "COMPARISON RESULT SHOULD BE: " << isNotEqualShouldBe << "\n\n";
    if (res == isNotEqualShouldBe) { std::cout << "TEST SUCCESSFULLY PASSED\n" << endl; }
    else
    {
        passedAllTests = false;
        std::cout << "TEST FAILED\n" << endl;
    }

    std::cout << "----------------------------------------------------------------\n" << endl;

    res = (biINT >= biSTR);

    std::cout << "|| Is first big_integer BIGGER OR EQUAL TO second big_integer? ||" << "\n"
              << "COMPARISON RESULT IS: " << res << "\n"
              << "COMPARISON RESULT SHOULD BE: " << isBiggerOrEqualShouldBe << "\n\n";
    if (res == isBiggerOrEqualShouldBe) { std::cout << "TEST SUCCESSFULLY PASSED\n" << endl; }
    else
    {
        passedAllTests = false;
        std::cout << "TEST FAILED\n" << endl;
    }

    std::cout << "----------------------------------------------------------------\n" << endl;

    res = (biINT <= biSTR);

    std::cout << "|| Is first big_integer SMALLER OR EQUAL TO second big_integer? ||" << "\n"
              << "COMPARISON RESULT IS: " << res << "\n"
              << "COMPARISON RESULT SHOULD BE: " << isSmallerOrEqualShouldBe << "\n\n";
    if (res == isSmallerOrEqualShouldBe) { std::cout << "TEST SUCCESSFULLY PASSED\n" << endl; }
    else
    {
        passedAllTests = false;
        std::cout << "TEST FAILED\n" << endl;
    }

    std::cout << "----------------------------------------------------------------\n" << endl;

    res = (biINT > biSTR);

    std::cout << "|| Is first big_integer BIGGER THAN second big_integer? ||" << "\n"
              << "COMPARISON RESULT IS: " << res << "\n"
              << "COMPARISON RESULT SHOULD BE: " << isBiggerShouldBe << "\n\n";
    if (res == isBiggerShouldBe) { std::cout << "TEST SUCCESSFULLY PASSED\n" << endl; }
    else
    {
        passedAllTests = false;
        std::cout << "TEST FAILED\n" << endl;
    }

    std::cout << "----------------------------------------------------------------\n" << endl;

    res = (biINT < biSTR);

    std::cout << "|| Is first big_integer SMALLER THAN second big_integer? ||" << "\n"
              << "COMPARISON RESULT IS: " << res << "\n"
              << "COMPARISON RESULT SHOULD BE: " << isSmallerShouldBe << "\n\n";
    if (res == isSmallerShouldBe) { std::cout << "TEST SUCCESSFULLY PASSED\n" << endl; }
    else
    {
        passedAllTests = false;
        std::cout << "TEST FAILED\n" << endl;
    }

    std::cout << "----------------------------------------------------------------\n" << endl;
}


void printCalculationReport(const string &addedShouldBe, const string &subtractedShouldBe,
                            const string &multipliedShouldBe, const string &dividedShouldBe,
                            const string &divideRemainderShouldBe)
{
    cout      << "\n!!! WARNING: THESE TESTS ASSUME ALL THE CONSTRUCTORS WORK PROPERLY.\n"
                 "MAKE SURE YOU'RE GETTING THE CORRECT BEHAVIOUR OF THE CONSTRUCTORS FIRST !!!\n"
    << endl;

    big_integer temp = biINT;
    big_integer resAdd(addedShouldBe);
    big_integer resSub(subtractedShouldBe);
    big_integer resMult(multipliedShouldBe);
    big_integer resDiv(dividedShouldBe);
    big_integer remDiv(divideRemainderShouldBe);
    string hhh = addedShouldBe;

    cout      << "\n+++++++++++++++++++++ CALCULATION REPORT +++++++++++++++++++++\n" << endl;

    std::cout << "|| ADD STRINGS ||" << "\n"
              << "THE ADDED_NUMBER_STR IS: " << (biINT + biSTR) << "\n"
              << "SAME BUT WITH += OPERATOR IS: " << (temp += biSTR) << "\n"
              << "THE ADDED_NUMBER_STR SHOULD BE: " << addedShouldBe << "\n\n";

    if (temp == resAdd) { std::cout << "TEST SUCCESSFULLY PASSED\n" << endl; }
    else
    {
        passedAllTests = false;
        std::cout << "TEST FAILED\n" << endl;
    }

    std::cout << "----------------------------------------------------------------\n" << endl;

    temp = biINT;

    std::cout << "|| SUBTRACT STRINGS ||" << "\n"
              << "THE SUBTRACTED_NUMBER_STR IS: " << (biINT - biSTR) << "\n"
              << "SAME BUT WITH -= OPERATOR IS: " << (temp -= biSTR) << "\n"
              << "THE SUBTRACTED_NUMBER_STR SHOULD BE: " << subtractedShouldBe << "\n\n";

    if (temp == resSub) { std::cout << "TEST SUCCESSFULLY PASSED\n" << endl; }
    else
    {
        passedAllTests = false;
        std::cout << "TEST FAILED\n" << endl;
    }

    std::cout << "----------------------------------------------------------------\n" << endl;

    temp = biINT;

    std::cout << "|| MULTIPLY STRINGS ||" << "\n"
              << "THE MULTIPLIED_NUMBER_STR IS: " << (biINT * biSTR) << "\n"
              << "SAME BUT WITH *= OPERATOR IS: " << (temp *= biSTR) << "\n"
              << "THE MULTIPLIED_NUMBER_STR SHOULD BE: " << multipliedShouldBe << "\n\n";

    if (temp == resMult) { std::cout << "TEST SUCCESSFULLY PASSED\n" << endl; }
    else
    {
        passedAllTests = false;
        std::cout << "TEST FAILED\n" << endl;
    }
    std::cout << "----------------------------------------------------------------\n" << endl;

    temp = biINT;

    std::cout << "|| DIVIDE STRINGS ||" << "\n"
              << "THE DIVIDED_NUMBER_STR IS: " << (biINT / biSTR) << "\n"
              << "SAME BUT WITH /= OPERATOR IS: " << (temp /= biSTR) << "\n"
              << "THE DIVIDED_NUMBER_STR SHOULD BE: " << dividedShouldBe << "\n\n";

    if (temp == resDiv) { std::cout << "TEST SUCCESSFULLY PASSED\n" << endl; }
    else
    {
        passedAllTests = false;
        std::cout << "TEST FAILED\n" << endl;
    }

    std::cout << "----------------------------------------------------------------\n" << endl;

    temp = (biINT % biSTR);

    std::cout << "|| DIVIDE REMAINDER ||" << "\n"
              << "THE DIVISION_REMAINDER_STR IS: " << temp << "\n"
//              << "SAME BUT WITH %= OPERATOR IS: " << (temp %= biSTR)
              << "THE DIVISION_REMAINDER_STR SHOULD BE: " << divideRemainderShouldBe << "\n\n";

    if (temp == remDiv) { std::cout << "TEST SUCCESSFULLY PASSED\n" << endl; }
    else
    {
        passedAllTests = false;
        std::cout << "TEST FAILED\n" << endl;
    }

    std::cout << "----------------------------------------------------------------\n" << endl;
}

int main()
{
    passedAllTests = true;


    printTrivialConstructionReport();

    // COMPARISON TEST:

    cout << "\n~~~~~~~~~~~~~~~~~~~~ COMPARISON TRIVIAL CASE A ~~~~~~~~~~~~~~~~~~~~\n";

    setTestValues(0, "0");
    reConstruct();

    printConstructionReport();
    printComparisonReport(true, false, true, true, false, false);


    cout << "\n~~~~~~~~~~~~~~~~~~~~ COMPARISON TRIVIAL CASE B ~~~~~~~~~~~~~~~~~~~~\n";

    setTestValues(10, "10");
    reConstruct();

    printConstructionReport();
    printComparisonReport(true, false, true, true, false, false);


    cout << "\n~~~~~~~~~~~~~~~~~~~~ COMPARISON TRIVIAL CASE C ~~~~~~~~~~~~~~~~~~~~\n";

    setTestValues(1, "0");
    reConstruct();

    printConstructionReport();
    printComparisonReport(false, true, true, false, false, true);

    cout << "\n~~~~~~~~~~~~~~~~~~~~ COMPARISON TRIVIAL CASE D ~~~~~~~~~~~~~~~~~~~~\n";

    setTestValues(0, "1");
    reConstruct();

    printConstructionReport();
    printComparisonReport(false, true, false, true, true, false);

    cout << "\n~~~~~~~~~~~~~~~~~~~~ COMPARISON TRIVIAL CASE E ~~~~~~~~~~~~~~~~~~~~\n";

    setTestValues(-1, "0");
    reConstruct();

    printConstructionReport();
    printComparisonReport(false, true, false, true, true, false);

    cout << "\n~~~~~~~~~~~~~~~~~~~~ COMPARISON TRIVIAL CASE F ~~~~~~~~~~~~~~~~~~~~\n";

    setTestValues(0, "-1");
    reConstruct();

    printConstructionReport();
    printComparisonReport(false, true, true, false, false, true);

    cout << "\n~~~~~~~~~~~~~~~~~~~~ COMPARISON TRIVIAL CASE G ~~~~~~~~~~~~~~~~~~~~\n";

    setTestValues(0, "-1");
    reConstruct();

    printConstructionReport();
    printComparisonReport(false, true, true, false, false, true);

    cout << "\n~~~~~~~~~~~~~~~~~~~~ COMPARISON TRIVIAL CASE H ~~~~~~~~~~~~~~~~~~~~\n";

    setTestValues(10, "-000");
    reConstruct();

    printConstructionReport();
    printComparisonReport(false, true, true, false, false, true);

    cout << "\n~~~~~~~~~~ Comparison Case special str const numbers A ~~~~~~~~~~\n";

    setTestValues(0, "000000100");
    reConstruct();

    printConstructionReport();
    printComparisonReport(false, true, false, true, true, false);

    cout << "\n~~~~~~~~~~ Comparison Case special str const numbers B ~~~~~~~~~~\n";

    setTestValues(0, "-002");
    reConstruct();

    printConstructionReport();
    printComparisonReport(false, true, true, false, false, true);

    cout << "\n~~~ COMPARISON CASE num and numStr are huge and num is slightly bigger ~~~\n";

    setAdvancedTestValues("918273645918273645", "918273645918273644");
    printComparisonReport(false, true, true, false, false, true);

    cout << "\n~~~ COMPARISON CASE num and numStr are huge and num is much bigger ~~~\n";

    setAdvancedTestValues("9182736459182736458745862", "918273645918273644");
    printComparisonReport(false, true, true, false, false, true);

    cout << "\n~~~ COMPARISON CASE num is a huge negative number and numStr is big ~~~\n";

    setAdvancedTestValues("-9182736459182736458745862", "918273645918273644");
    printComparisonReport(false, true, false, true, true, false);

    cout << "\n~~ COMPARISON CASE numStr is a huge negative number and num is positive & big ~~\n";

    setAdvancedTestValues("918273645918273644", "-9182736459182736458745862");
    printComparisonReport(false, true, true, false, false, true);

    cout << "\n~~~ COMPARISON CASE num and numStr are big (but fit into long long) ~~~\n";

    setAdvancedTestValues("9182736459182736458", "918273645918");
    printComparisonReport(false, true, true, false, false, true);



    // CALCULATION TEST:

    // Some of the true results were calculated with:
    // https://defuse.ca/big-number-calculator.htm

    cout << "\n~~~~~~~~~~~~~~~~~~~~ TRIVIAL CASE A ~~~~~~~~~~~~~~~~~~~~\n";

    setTestValues(1, "1");
    reConstruct();

    printConstructionReport();
    printCalculationReport("2", "0", "1", "1", "0");

    cout << "\n~~~~~~~~~~~~~~~~~~~~ TRIVIAL CASE B ~~~~~~~~~~~~~~~~~~~~\n";

    setTestValues(0, "0");
    reConstruct();

    printConstructionReport();
    printCalculationReport("0", "0", "0", "0", "0");

    cout << "\n~~~~~~~~~~~~~~~~~~~~ TRIVIAL CASE C ~~~~~~~~~~~~~~~~~~~~\n";

    setTestValues(1, "0");
    reConstruct();

    printConstructionReport();
    printCalculationReport("1", "1", "0", "0", "0");

    cout << "\n~~~~~~~~~~~~~~~~~~~~ TRIVIAL CASE D ~~~~~~~~~~~~~~~~~~~~\n";

    setTestValues(0, "1");
    reConstruct();

    printConstructionReport();
    printCalculationReport("1", "-1", "0", "0", "0");

    cout << "\n~~~~~~~~~~~~~~~~~~~~ TRIVIAL CASE E ~~~~~~~~~~~~~~~~~~~~\n";

    setTestValues(0, "-10");
    reConstruct();

    printConstructionReport();
    printCalculationReport("-10", "10", "0", "0", "0");

    cout << "\n~~~~~~~~~~~~~~~~~~~~ TRIVIAL CASE F ~~~~~~~~~~~~~~~~~~~~\n";

    setTestValues(-10, "0");
    reConstruct();

    printConstructionReport();
    printCalculationReport("-10", "-10", "0", "0", "0");

    cout << "\n~~~~~~~~~~~~~~~~~~~~ TRIVIAL CASE G ~~~~~~~~~~~~~~~~~~~~\n";

    setTestValues(-21, "4");
    reConstruct();

    printConstructionReport();
    printCalculationReport("-17", "-25", "-84", "-5", "-1");

    cout << "\n~~~~~~~~~~~~~~~~~~~~ TRIVIAL CASE H ~~~~~~~~~~~~~~~~~~~~\n";

    setTestValues(10, "-000");
    reConstruct();

    printConstructionReport();
    printCalculationReport("10", "10", "0", "0", "0");

    cout << "\n~~~~~~~~~~~~~~~~~~~~ TRIVIAL CASE I ~~~~~~~~~~~~~~~~~~~~\n";

    setTestValues(21, "-4");
    reConstruct();

    printConstructionReport();
    printCalculationReport("17", "25", "-84", "-5", "1");

    cout << "\n~~~~~~~~~~ Case special str const numbers A ~~~~~~~~~~\n";

    setTestValues(0, "000000100");
    reConstruct();

    printConstructionReport();
    printCalculationReport("100", "-100", "0", "0", "0");

    cout << "\n~~~~~~~~~~ Case special str const numbers B ~~~~~~~~~~\n";

    setTestValues(0, "-002");
    reConstruct();

    printConstructionReport();
    printCalculationReport("-2", "2", "0", "0", "0");


    cout << "\n~~~~~~~~~~ CASE numStr (divisor) is bigger than num ~~~~~~~~~~\n";

    setTestValues(1, "2");
    reConstruct();

    printConstructionReport();
    printCalculationReport("3", "-1", "2", "0", "1");

    cout << "\n~~~~~~~~~~ CASE numStr equal number, different sign ~~~~~~~~~~\n";

    setTestValues(-10, "10");
    reConstruct();

    printConstructionReport();
    printCalculationReport("0", "-20", "-100", "-1", "0");

    cout << "\n~~~~~~~~~~ CASE numStr equals num (both pos) ~~~~~~~~~~\n";

    setTestValues(500, "500");
    reConstruct();

    printConstructionReport();
    printCalculationReport("1000", "0", "250000", "1", "0");

    cout << "\n~~~~~~~~~~~~~~~~~~~~ CASE numStr equals num (both neg) ~~~~~~~~~~~~~~~~~~~~\n";

    setTestValues(-10, "-10");
    reConstruct();

    printConstructionReport();
    printCalculationReport("-20", "0", "100", "1", "0");

    cout << "\n~~~~~ CASE num and numStr are small and 'well behaved' (divide perfectly) ~~~~~\n";

    setTestValues(3750, "150");
    reConstruct();

    printConstructionReport();
    printCalculationReport("3900", "3600", "562500", "25", "0");

    cout << "\n~~~~~~~~~~ CASE num and numStr are small but DON'T divide perfectly ~~~~~~~~~~\n";

    setTestValues(3750, "151");
    reConstruct();

    printConstructionReport();
    printCalculationReport("3901", "3599", "566250", "24", "126");

    cout << "\n~~~~~~~~~~ CASE num and numStr are huge and num is slightly bigger ~~~~~~~~~~\n";

    setAdvancedTestValues("918273645918273645", "918273645918273644");
    printCalculationReport("1836547291836547289", "1",
            "843226488788038999128124891183312380", "1", "1");

    cout << "\n~~~~~~~~~~ CASE num and numStr are huge and num is much bigger ~~~~~~~~~~\n";

    setAdvancedTestValues("9182736459182736458745862", "918273645918273644");
    printCalculationReport("9182737377456382377019506", "9182735540909090540472218",
            "8432264887880389999312343497271208368661128", "10000000", "18745862");

    cout << "\n~~~~~~~~~~ CASE num is a huge negative number and numStr is big ~~~~~~~~~~\n";

    setAdvancedTestValues("-9182736459182736458745862", "918273645918273644");
    printCalculationReport("-9182735540909090540472218", "-9182737377456382377019506",
            "-8432264887880389999312343497271208368661128", "-10000000", "-18745862");

    cout << "\n~~~~~~~ CASE numStr is a huge negative number and num is positive & big ~~~~~~~\n";

    setAdvancedTestValues("918273645918273644", "-9182736459182736458745862");
    printCalculationReport("-9182735540909090540472218", "9182737377456382377019506",
            "-8432264887880389999312343497271208368661128", "0", "918273645918273644");

    cout << "\n~~~~~~~~~~ CASE num and numStr are big (but fit into long long) ~~~~~~~~~~\n";

    setAdvancedTestValues("9182736459182736458", "918273645918");
    printCalculationReport("9182737377456382376", "9182735540909090540",
            "8432264887877877197891801478444", "10000000", "2736458");

    if (passedAllTests)
    {
        cout << "YOU PASSED ALL THE TESTS! :) \n";
    }
    else
    {
        cout << "THERE IS STILL A TEST YOU FAILED... :( \n";
        cout << "LOOK FOR: TEST FAILED\n";
    }


    // SET TEST:
//    cout << "\n---------------- MINIMAL SET TEST, NOT VERY ORGANIZED ----------------\n";
//    my_set setDEF;
//    my_set setDEF2;
//
//    big_integer bi1("50");
//    big_integer bi2("0");
//    big_integer bi3("-3");
//    big_integer bi4("-36536536");
//    big_integer bi5("48348634");
//
//    big_integer bi6("50");
//    big_integer bi7("11");
//    big_integer bi8("9");
//    big_integer bi9("12");
//    big_integer bi10("8");
//    big_integer bi11("10");
//
//    setDEF.add(bi1);
//    setDEF.add(bi2);
//    setDEF.add(bi3);
//    setDEF.add(bi4);
//    setDEF.add(bi5);
//    setDEF.add(bi2);
//    setDEF.add(bi1);
//
//    my_set setCOPY (setDEF);
//    //cout << setCOPY;
//
//    setDEF.remove(bi5);
//   setDEF.remove(bi2);
//    //cout << setDEF;
//
//    setDEF2.add(bi6);
//    setDEF2.add(bi7);
//    setDEF2.add(bi8);
//    setDEF2.add(bi9);
//    setDEF2.add(bi10);
//    // cout << setDEF2;
//
//    my_set uni = (setDEF | setDEF2);
//
//    cout << uni.is_in_set(bi11) << "\n";
//    cout << uni;

}