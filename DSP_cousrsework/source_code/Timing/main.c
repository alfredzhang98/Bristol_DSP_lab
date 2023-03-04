#include <xdc/std.h>
#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Task.h>

#include <xdc/runtime/Types.h>
#include <xdc/runtime/Timestamp.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


// define variables for timing
int start, stop, tdiff;


/*
 *  ======== main ========
 */
void main(void)
{
   	//Record start time
	start = Timestamp_get32();

   	// Task to be completed
	System_printf("Doing some tasks\n");
	System_flush();

   	//Record stop time
	stop = Timestamp_get32();

   	//Print elapsed time
   	tdiff = stop-start;
   	System_printf("%d cycles used\n", tdiff);

   	return;
}

