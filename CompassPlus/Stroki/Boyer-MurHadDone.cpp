#include <stdio.h>
#include <assert.h>
//#include <iostream>
#include <windows.h>

const int MAX_SIZE = 200;
const int ALPH_SIZE = 255;

struct String
{
    char arr[MAX_SIZE];
    int size;

    bool set(char* val, int n);
    bool set(char* s);
    bool copyFrom(String* another);
    int findStr(String* obr);
    int find(String* obr);
    void calcPrefixFunction(String* s, int* p);
    void reverse(String* obr);

    void readArray();
    void printArray();
};

int Max(int a, int b);
int Min(int a, int b);
void calcRightPos(String* obr, int* p);
void calcSdvig(String* obr, int* sdvig);
void allTests();
void testCalcSdvig();
void testPrefix();

int main()
{
    allTests();

    String str;
    String obr;

    str.size = 5;

    String s1;
    //printf("Stroka:\n");
    s1.set("kataka", 6);
    //s1.printArray();

    //printf("Obrazec:\n");
    obr.set("tak", 3);
    //obr.printArray();

    printf("Index:%d\n", s1.find(&obr));

    return 0;
}

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

void calcSdvig(String* obr, int* sdvig)
{
    String reversedObr;

    int pref[obr->size];
    int pref1[obr->size];
    calcPrefixFunction(obr, pref);

    obr->reverse(&reversedObr);
    calcPrefixFunction(&reversedObr, pref1);

    sdvig[0] = 1;
    for (int i = 1; i <= obr->size; i++)
    {
        sdvig[i] = obr->size - pref[obr->size - 1];

    }
    for (int i = 1; i < obr->size; i++)
    {
        sdvig[pref1[i]] = Min(sdvig[pref1[i]], i - pref1[i] + 1);
    }
}

void calcRightPos(String* obr, int* rp)
{
    for (int i = 0; i < obr->size - 1; i++)
    {
        rp[obr->arr[i]] = -1;
    }
    for (int i = 0; i < obr->size - 1; i++)
    {
        rp[obr->arr[i]] = i;
    }
}

int Max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int Min(int a, int b)
{
    if (a < b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int String::find(String* obr)
{
    int rp[ALPH_SIZE];
    calcRightPos(obr, rp);
    int sdvig[obr->size];
    calcSdvig(obr, sdvig);
    int k = 0;
    while(k <= size - obr->size)
    {
        for(int j = obr -> size - 1; j >= 0; j--)
        {
            if(obr->arr[j] != arr[k + j])
            {
                int stopSdvig = j - rp[arr[k + j]];
                int sufSdvig = sdvig[obr->size - 1 - j];
                k = k + Max(sufSdvig, stopSdvig);
                break;
            }
            else if(j == 0)
            {
                return k;
            }
        }
    }
    return -1;
}

bool String::set(char* s)
{
    int idx = 0;
    while(s[idx] != 0 && idx < MAX_SIZE)
    {
        arr[idx] = s[idx];
        idx++;
    }
    size = idx;
    if(s[idx] != 0)
    {
        return false;
    }
    else
    {
        return true;
    }
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

void String::reverse(String* obr)
{
    for (int i = 0; i < (size + 1) / 2; i++)
    {
        int reverseA = arr[i];
        obr->arr[i] = arr[size - 1 - i];
        obr->arr[size - 1 - i] = reverseA;
    }
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


/*
void testCalcSdvig()
{
    String sdv;
    //void calcSdvig(String* obr, int* sdvig)
    sdv.set("trulala");
    int s[7];
    String o;
    o.set("rul");
    calcSdvig()
}
*/

void testPrefix()
{
    int p[ALPH_SIZE];
    String pr;
    pr.set("kabakaka");
    calcPrefixFunction(&pr, p);
    assert(p[0] == 0);
    assert(p[1] == 0);
    assert(p[2] == 0);
    assert(p[3] == 0);
    assert(p[4] == 1);
    assert(p[5] == 2);
    assert(p[6] == 1);
    assert(p[7] == 2);
}

void allTests()
{
    testPrefix();
    //testFindStr1();
}


