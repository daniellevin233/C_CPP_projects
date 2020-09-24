#include <stdio.h>
#include <assert.h>

const int N = 5;
const int MAX_SIZE = 200;

struct Vector
{
    int arr[MAX_SIZE];
    int size;
    int findElement(int q);
    int findMaxElement();
    int findMinElement();

    void printArray();
    void shiftRight();
    void readArray();
};

void printArray(int arr[], int n);
void allTests();

int main ()
{
    allTests();

    Vector v;
    v.size = 5;

    int arr[N];
    int q;

    v.readArray();
    printf("Maximum:%d\n", v.findMaxElement());
    printf("Minimum:%d\n", v.findMinElement());
    printf("Vvedite nuzhniy element:\n", &q);
    scanf("%d");
    printf("%d", v.findElement(q));

    return 0;
}

int Vector::findMaxElement()
{
    int max = arr[0];
    for (int i = 1; i < size; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

int Vector::findMinElement()
{
    int min = arr[0];
    for (int i = 1; i < size; i++)
    {
        if (arr[i] < min)
        {
            min = arr[i];
        }
    }
    return min;
}

int Vector::findElement(int q)
{
    for (int i = 0; i < size; i++)
    {
        if (q == arr[i])
        {
            return i;
        }
    }
    return -1;
}

void Vector::readArray()
{
    printf("Vvedite %d elementov:\n", size);
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
    }
}

void Vector::printArray()
{
    for (int i = 0; i < size; i++)
    {
        printf("%d\n", arr[i]);
    }
}

void testFindElement()
{
    Vector v;
    v.size = 3;
    //int arrFind[] = {1, 2, 3, 4, 5};
    v.arr[0] = 1;
    v.arr[1] = 2;
    v.arr[2] = 3;
    int findE = v.findElement(3);
    assert(findE == 2);
}

void testFindMaxElement()
{
    Vector v;
    v.size = 3;
    //int arrMaxFind[] = {1, 122, 3092, 234, 305};
    v.arr[0] = 1;
    v.arr[1] = 2;
    v.arr[2] = 3;
    int findMaxE = v.findMaxElement();
    assert(findMaxE == 3);
}

void allTests()
{
    testFindElement();
    testFindMaxElement();
}
