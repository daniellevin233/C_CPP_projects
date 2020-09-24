#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <windows.h>

const int MAX_SIZE = 200;


struct String
{
    char arr[MAX_SIZE];
    int size;


    bool set(char* val, int n);
    bool copyFrom(String* another);
    int findStr1(String* obr);
    int findStr2(String* obr);
    int preffics(int index);
    void calcPrefixFunction(String* s, int* p);

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

    int index;

    str.size = 5;

    String s1;
    printf("Stroka:\n");
    s1.set("kataka", 6);
    s1.printArray();

    printf("Obrazec:\n");
    obr.set("bak", 3);
    obr.printArray();

    //printf("Index:%d\n", calcPrefixFunction(s, *p));
    //printf("Index:%d\n", s1.preffics(5));


    return 0;
}

/*int String::preffics(int index)
{
    for(int i = index; i <= size; i++)
    {
        for(int k = 0; k <= i; k++)
        {
            if(arr[k] == arr[i - k])
            {
                for(int j = 0; j < i; j++)
                {
                    if(arr[k + j] == arr[i - k - j])
                    {
                        return k + j;
                    }
                    else
                    {
                        j++;
                    }
                }
            }
            else
            {
                i++;
            }
        }
    }
    return 0;
}
*/

void calcPrefixFunction(String* s, int* p)
{
    p[0] = 0;
    for(int i = 1; i < s->size; i++)
    {
        int l = p[i - 1];
        while(l > 0 && s->arr[l] != s->arr[i])
        {
            l = p[l - 1];
        }
        if(s->arr[l] == s->arr[i])
        {
            p[i] = l + 1;
        }
        else
        {
            p[i] = 0;
        }
    }
}

/*int String::findStr2(String* obr)
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
            for(int k = 0; k < obr->size; k++)
            {

            }
            if (obr->arr[j] = arr[i + j])
            {
                j =
            }
            else
            {
                i = i + j - alphabet[arr[i + j]];
            }
            match = false;
            break;
        }
        if (match)
        {
            return i;
        }
    }

}
*/
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

/*void testFindStr1()
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
*/

void testCalcPrefix()
{
    String c1;



}

void allTests()
{
    //testFindStr1();
    testCalcPrefix();
}


