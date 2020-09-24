#include <stdio.h>
#include <assert.h>

const int N = 6;
const int M = 3;

void readArray(int a[], int n);
void printArray(int a[], int n);

int sumArray(int a[], int n);

int main()
{
    int arr[N];
    int a2[M];

    readArray(a2, M);
    printArray(a2, M);

    printf("Summa = %d\n", sumArray(a2, M));
}

void readArray(int a[], int n)
{
    printf("Vvedite %d elementov:\n", n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
}

void printArray(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d\n", a[i]);
    }
}

int sumArray(int a[], int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum = a[i] + sum;
    }
    return sum;
}











