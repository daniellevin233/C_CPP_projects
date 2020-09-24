#include <stdio.h>
#include <assert.h>

const int MAX_SIZE = 200;

struct String
{
    char arr[MAX_SIZE];
    int size;
    int findString(String);

    void readArray();
    void printArray();
};

int main()
{
    String s;

    s.size = 5;

    s.findString(s);
    s.readArray();
    s.printArray();

    return 0;
}

int String::findString(String)
{

    int x = 3;
    char arr2[x];

    for (int i = 0; i < x; i++)
    {
        if (arr[i] == arr2[i])
        {
            return 1;
        }
        return -1;
    }
}

void String::readArray()
{
    printf("Vvedite chto-to:\n");
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
}
