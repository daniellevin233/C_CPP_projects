#include <stdio.h>

// constants of ASCII table
#define UPPER_LET_BEGIN 65
#define UPPER_LET_FINISH 90
#define LOWER_LET_BEGIN 97
#define LOWER_LET_FINISH 122
#define ALPHABET_LENGTH 26

// constants of enciphering
#define MIN_KEY (-25)
#define MAX_KEY 25

/**
 * Function that treats (encipher) one symbol.
 *
 * Function changes only lower and upper letters, all other stuff will be leaved the same.
 *
 * @param sym - char to be enciphered
 * @param cipher_key - int - constant of cipher
 */
void encipherOneSymbol(char sym, int const cipher_key)
{
    if ((sym >= UPPER_LET_BEGIN) && (sym <= UPPER_LET_FINISH)) // we've got upper letter
    {
        // add ALPHABET_LENGTH before modulus for treating negative keys
        int new_sym = UPPER_LET_BEGIN + \
                    (ALPHABET_LENGTH + (int)sym + cipher_key - UPPER_LET_BEGIN) \
                    % ALPHABET_LENGTH;
        printf("%c", new_sym);
    }
    else if ((sym >= LOWER_LET_BEGIN) && (sym <= LOWER_LET_FINISH)) // we've got lower letter
    {
        // add ALPHABET_LENGTH before modulus for treating negative keys
        int new_sym = LOWER_LET_BEGIN +
                      (ALPHABET_LENGTH + (int)sym + cipher_key - LOWER_LET_BEGIN) \
                      % ALPHABET_LENGTH;
        printf("%c", new_sym);
    }
    else // letter is haven't got
    {
        printf("%c", sym);
    }
}

/**
 * Function treats one buffer of symbols which contains 'fullness' symbols by sending
 * every symbol to the encipherOneSymbol function
 *
 * @param fullness - number of symbols in given buffer (array)
 * @param array - buffer of chars for enciphering
 * @param cipher_key - int - constant of cipher
 */
void treatOneBuffer(int fullness, char *array, int const cipher_key)
{
    int k;
    for(k = 0; k < fullness; k++)
    {
        encipherOneSymbol(array[k], cipher_key);
    }
}

/**
 * The main function handling the program process
 *
 * Firstly function reads cipher key, in case of invalidity error message printed and
 * program closed.
 * Then the buffer is filling while it won't be EOF or buffer will be full.
 * Sending the buffer to treatOneBuffer for enciphering.
 *
 * @return 1 if input cipher key is not valid, 0 otherwise
 */
int encipheringMain()
{
    char text_input[512];
    int fullness, cipher_key;
    // Requesting cipher key and checking its validity
    if ((scanf("%d ", &cipher_key) != 1) || (cipher_key > MAX_KEY) || (cipher_key < MIN_KEY))
    {
        fprintf(stderr, "The cipher key is not valid.");
        return 1;
    }
    // filling the buffer until its fullness or EOF
    while((scanf("%512c%n", text_input, &fullness)) != EOF)
    {
        treatOneBuffer(fullness, text_input, cipher_key);
    }
    return 0;
}

/**
 * Main calls to encipheringMain for making caesar cipher
 * Read more about caesar cipher here: https://en.wikipedia.org/wiki/Caesar_cipher
 *
 * @return 0 if all the inputs were valid, 1 otherwise
 */
int main()
{
    encipheringMain();
    return 0;
}