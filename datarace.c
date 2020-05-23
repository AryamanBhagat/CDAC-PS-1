#include <stdio.h>
#include <omp.h>

int main()
{
    int i, sum = 0;
    int a[100]; 

    for (i = 1; i < 100; i++) {
       a[i] = i;
    }
 

#pragma omp parallel for reduction(+:sum)
    for (i = 1; i < 99; i++) {
        a[i] = a[i] + 1;
        sum = sum + a[i + 1];
    }

    printf("%d\n", sum); 
}