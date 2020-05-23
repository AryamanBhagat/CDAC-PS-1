#include <omp.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
 int n = 1000;
 double vec[n], sca;
 for(int i = 0; i < n; i++)
  vec[i] = i*20.0;
  sca = 3.14;
 int i;
 int chunksize = 50; //my system has 692 threads, I am hoping that this way only 20 threads will be used
 #pragma omp parallel shared(vec, sca, chunksize) private(i)
 {
   #pragma omp for schedule(dynamic, chunksize) nowait
   for(i = 0; i < n; i++)
   {
     vec[i] = vec[i] + sca;
     printf("%d, %d\n", i, omp_get_thread_num());
   }
 }
 
 for(int i = 0; i < n; i++)
  printf("%lf ", vec[i]);

 }