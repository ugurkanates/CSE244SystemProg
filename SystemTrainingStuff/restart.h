#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "restart.h"
#include <errno.h>




	pid_t r_wait(int *stat_loc) {
	 int retval;
 	while (((retval = wait(stat_loc)) == -1) && (errno == EINTR)) ;
 	return retval;

	}
