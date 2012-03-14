/*
 * =====================================================================================
 *
 *       Filename:  strftime_example.c
 *
 *    Description:  linux manpage example
 *
 *        Version:  1.0
 *        Created:  Wednesday 14 March 2012 05:10:19  GMT
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

/* /home/nxd/Progs/xtcc/xtcc/qscript/stubs/simple_compiler/stubs>./a.out '%Y%d%m_%H%M%S'
 *
 * invoke as above
 *  */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
	char outstr[200];
	time_t t;
	struct tm *tmp;

	t = time(NULL);
	tmp = localtime(&t);
	if (tmp == NULL) {
	perror("localtime");
	exit(EXIT_FAILURE);
	}

	if (strftime(outstr, sizeof(outstr), argv[1], tmp) == 0) {
	fprintf(stderr, "strftime returned 0");
	exit(EXIT_FAILURE);
	}

	printf("Result string is \"%s\"\n", outstr);
	exit(EXIT_SUCCESS);
}

