#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <windows.h>

const int MAX_SIZE = 200;

struct String
{
    char arr[MAX_SIZE];
    int size;
    //int a;

    bool set(char* val, int n);
    bool copyFrom(String* another);
    int findStr1(String* obr);

    void readArray();
    void printArray();
};

void allTests();

int main()
{
    allTests();

    String s;
    String str;
    String obr;

    str.size = 5;

    String s1;
    printf("Stroka:\n");
    s1.set("qwertyty", 8);
    s1.printArray();

    printf("Obrazec:\n");
    obr.set("yty", 3);
    obr.printArray();

    printf("Index:%d\n", s1.findStr1(&obr));

    return 0;
}

int String::findStr1(String* obr)
{
    int alphabet[255];
    for(int i = 0; i < 255; i++)
    {
        alphabet[i] = -1;
    }
    for(int i = 0; i < obr->size - 1; i++)
    {
        alphabet[obr->arr[i]] = i;
    }
    int i = 0;
    while(i <= size - obr->size)
    {
        bool match = true;
        for(int j = obr->size - 1; j >= 0 ; j--)
        {
            if (obr->arr[j] != arr[i + j])
            {
                if(j - alphabet[obr->arr[i + j]] <= 0)
                {
                    i++;
                }
                else
                {
                    i = i + j - alphabet[arr[i + j]];
                }
                match = false;
                break;
            }
        }
        if (match)
        {
            return i;
        }
    }
    return -1;
}

void String::readArray()
{

    for (int i = 0; i < size; i++)
    {
        scanf("%c", &arr[i]);
    }
}

void String::printArray()
{
    for (int i = 0; i < size; i++)
    {
        printf("%c", arr[i]);
    }
    printf("\n");
}

bool String::set(char* val, int n)
{
    if( n >= 0 && n <= MAX_SIZE)
    {
        for(int i = 0; i < n; i++)
        {
            arr[i] = val[i];
        }
        size = n;
        return true;
    }
    return false;
}

void testFindStr1()
{
    String t1;
    t1.set("ogogo", 5);
    String t2;
    t2.set("gog", 3);
    int result = t1.findStr1(&t2);
    printf("test: %d\n", result);
    assert(result == 1);

    String tt1;
    tt1.set("ogogo", 5);
    String tt2;
    tt2.set("dog", 3);
    tt1.findStr1(&tt2);
    assert(tt1.findStr1(&tt2) == -1);

    String ttt1;
    ttt1.set("ogogo", 5);
    String ttt2;
    ttt2.set("dogdog", 6);
    ttt1.findStr1(&ttt2);
    assert(ttt1.findStr1(&ttt2) == -1);
}

void allTests()
{
    testFindStr1();
}

