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

    void readArray();
    void printArray();
};

void allTests();

int main()
{
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

    return 0;
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

/*bool String::copyFrom(String* another)
{
    return set(another->arr, another->size);
}

void testCopyFrom()
{
    String s;
    s.size = 5;
    for(int i = 0; i < s.size; i++)
    {
        s.arr[i] = val[i];
    }
    assert(val[1] == "M");
}

void allTests()
{
    testCopyFrom();
}
*/
