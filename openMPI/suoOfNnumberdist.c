#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

#define MASTER 0        /* task ID of master task */

int main (int argc, char *argv[])
{
    int	homeSum,         /* value of i for current task */
    sum,	        /* sum of n numbers */
    Tsum;          //final sum
    int	taskid,	        /* task ID - also used as seed number */
	numtasks,       //number of tasks, also equal to number to which you want to add, one process is to be created for each integer upto n
	rc,             /* return code */
	i;
    MPI_Status status;

    /* Obtain number of tasks and task ID */
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD,&taskid);
    printf ("MPI task %d has started...\n", taskid);



   /* Use MPI_Reduce to sum values of homepi across all tasks 
    * Master will store the accumulated value in pisum 
    * - homepi is the send buffer
    * - pisum is the receive buffer (used by the receiving task only)
    * - the size of the message is sizeof(double)
    * - MASTER is the task that will receive the result of the reduction
    *   operation
    * - MPI_SUM is a pre-defined reduction function (double-precision
    *   floating-point vector addition).  Must be declared extern.
    * - MPI_COMM_WORLD is the group of tasks that will participate.
    */
   homeSum = taskid;
   rc = MPI_Reduce(&homeSum, &sum, 1, MPI_INT, MPI_SUM,
                   MASTER, MPI_COMM_WORLD);

   /* Master computes average for this iteration and all iterations */
   if (taskid == MASTER) {
      printf("   sum of n numbers is = %d\n",
              sum);
   }


MPI_Finalize();
return 0;
}





