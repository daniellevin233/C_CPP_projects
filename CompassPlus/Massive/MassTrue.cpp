#include <stdio.h>

const int N = 5;
const int M = 3;

int main()
{
    int arr[N];
    int arry[M];

    for (int i = 0; i < N; i++)
    {
        scanf("%d", &arr[i]);
    }
    for (int i = 0; i < N; i++)
    {
        printf("%d\n", arr[i]);
    }
    for (int i = 0; i < M; i++)
    {
        scanf("%d", &arry[i]);
    }
    for (int i = 0; i < M; i++)
    {
        printf("%d\n", arry[i]);
    }
}



