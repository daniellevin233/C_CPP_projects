#include <stdio.h>

/**
 * Function counts the "power_value" power of the number "base"
 * @param base - double number to be powered
 * @param power_value - integer number signing the power
 * @return the result of ("base")^("power_value")
 */
double power(double base, int power_value)
{
    if (power_value <= 1)
    {
        return base;
    }
    return base * power(base, (power_value - 1));
}

/**
 * Recursive function for counting sin(input_value)
 * @param input_value - double (positive) number sinus of whom we are counting
 * @return double - approximated result of sin(input_value)
 */
double mySinHp(double const input_value)
{
    if (input_value < 0.01)
    {
        return input_value;
    }
    else
    {
        double recursive_value = mySinHp(input_value / 3);
        return (3 * recursive_value - 4 * power(recursive_value, 3));
    }
}

/**
 * Function for counting sin(input_value)
 *
 * In the case of negative input_value, using the formula "sin(x) = -sin(-x)" for passing
 * the positive value to mySinHp()
 *
 * @param input_value - double number sinus of whom we are counting
 * @return double - result of mySinHp(input_value)
 */
double mySin(double const input_value)
{
    if (input_value < 0)
    {
        return -mySinHp(-input_value); // sin(x) = -sin(-x)
    }
    else
    {
        return mySinHp(input_value);
    }
}

/**
 * Main represents the 'sin' operation of a calculator
 *
 * First requesting the input value from user, in the case of its invalidity error message
 * is printed and program stops.
 * Then counting sinus of x by calling to function mySin.
 *
 * @return 1 if input is invalid, 0 otherwise.
 */
int main()
{
    double input_value;
    if (scanf("%lf", &input_value) != 1)
    {
        fprintf(stderr, "The input is not valid.");
        return 1;
    }
    double result = mySin(input_value);
    printf("%lf\n", result);
    return 0;
}