#include <stdio.h>
#include <assert.h>

const int MAX_SIZE = 200;

struct String
{
    char arr[MAX_SIZE];
    int size;

    bool set(char* val, int n);
    bool copyFrom(String* another);
    int findStr(String* obr);
    int compareTo(String* some);

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
    obr.set("ty", 2);
    obr.printArray();

    printf("Index:%d\n", s1.findStr(&obr));

    String c1;
    printf("Slovo #1:\n");
    c1.set("Grob", 4);
    c1.printArray();

    printf("Slovo #2:\n");
    some.set("Grib", 4);
    some.printArray();

    printf("Itog:\n", c1.compareTo(&some));

    return 0;
}

int String::compareTo(String* some)
{
    if (c1.size > some.size)
    {
        return 1;
    }
    else if (c1.size < some.size)
    {
        return -1;
    }
    for(int i = 0; i < c1.size)

}

int String::findStr(String* obr)
{
    for(int i = 0; i <= size - obr->size; i++)
    {
        bool match = true;
        for(int k = 0; k < obr->size; k++)
        {
            if (obr->arr[k] != arr[i + k])
            {
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

void testFindStr()
{
    String t1;
    t1.set("ogogo", 5);
    String t2;
    t2.set("gog", 3);
    t1.findStr(&t2);
    assert(t1.findStr(&t2) == 1);

    String tt1;
    tt1.set("ogogo", 5);
    String tt2;
    tt2.set("dog", 3);
    tt1.findStr(&tt2);
    assert(tt1.findStr(&tt2) == -1);

    String ttt1;
    ttt1.set("ogogo", 5);
    String ttt2;
    ttt2.set("dogdog", 6);
    ttt1.findStr(&ttt2);
    assert(ttt1.findStr(&ttt2) == -1);
}

void allTests()
{
    testFindStr();
}

