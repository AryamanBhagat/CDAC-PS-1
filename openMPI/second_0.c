/* 
 * This program demonstrates the use of MPI_Alltoall when
 * transpsong a square matrix.
 * For simplicity, the number of processes is 4 and the dimension
 * of the matrix is fixed to 128
 */

#include <stdio.h>
#include <mpi.h>

void
trans (double *a, int n)

{
  int i, j;
  int ij, ji, l;
  double tmp;
  ij = 0;
  l = -1;
  for (i = 0; i < n; i++)
    {
      l += n + 1;
      ji = l;
      ij += i + 1;
      for (j = i+1; j < n; j++)
	{
	  tmp = a[ij];
	  a[ij] = a[ji];
	  a[ji] = tmp;
	  ij++;
	  ji += n;
	}
    }
}

int
main (int argc, char *argv[])
{
  double a[128][32];
  double b[128][32];

  int i, j, nprocs, rank;

  MPI_Init (&argc, &argv);
  MPI_Comm_size (MPI_COMM_WORLD, &nprocs);
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);

  if(rank == 0)
  {
    printf("Transposing a 128x128 matrix, divided among 4 processors\n");
  }
  if (nprocs != 4)
    {
      if (rank == 0)
	printf ("Error, number of processes must be 4\n");
      MPI_Finalize ();
      return 1;
    }

//I am not taking any input, I am just building a unique matrix in each process
  for (i = 0; i < 128; i++)
    for (j = 0; j < 32; j++)
      a[i][j] = 1000 * i + j + 32 * rank; 

  MPI_Alltoall (&a[0][0],	
		32 * 32,	
		MPI_DOUBLE,	
		&b[0][0],	
		32 * 32,	
		MPI_DOUBLE,	
		MPI_COMM_WORLD); //https://www.youtube.com/watch?v=oE3ed3Bi74Q


  for (i = 0; i < 4; i++)
      trans (&b[i * 32][0], 32);

  MPI_Finalize ();
  return 0;
}

