#include <omp.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
 int n = 10;
 double vec[n], mat[n][n];
 for(int i = 0; i < n; i++)
  vec[i] = i*20.0;
 for(int i = 0; i < n; i++)
   for(int j = 0;j < n; j++)
     mat[i][j] = (i*3.14) + (j*1.414);
 
 int i, j;
 //int chunksize = 10;
 #pragma omp parallel shared(vec, mat) private(i, j)
 {
   #pragma omp for nowait collapse(2)
   for(i = 0; i < n; i++)
     {
         for(j = 0; j < n; j++)
         {
           mat[i][j] *= vec[i];    
           printf("%d, %d, tid %d\n", i, j, omp_get_thread_num());  
         }
              
     }
 }
 
  for(int i = 0; i < n; i++)
  {
    for(int j = 0;j < n; j++)
     printf("%lf ", mat[i][j]);
    printf("\n");
  }
 }