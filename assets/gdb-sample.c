#include <stdio.h>

int nGlobalVar = 0;

int tempFunction(int a, int b)
{
    for (int i  = 0; i < 3; i++)
    {
        a ++;
        b ++;
    }
    return a+b;

}

int main()
{
   int n;
    n = 1;
    n++;
    n--;

    nGlobalVar += 100;
    nGlobalVar -= 12;

    printf("n = %d, nGlobalVar = %d \n", n, nGlobalVar);

    n = tempFunction(1, 2);
    printf("n = %d", n);

    return 0;
}