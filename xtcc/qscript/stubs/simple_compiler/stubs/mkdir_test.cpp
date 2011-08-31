#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main()
{
	mode_t my_mode = S_IRUSR | S_IWUSR | S_IXUSR;

	struct stat dir_exists;
	if (stat("b_test_dir", &dir_exists) <0) {
		//char * err_str = strerror(errno);
		perror(0);
		//printf(" error: %s\n", err_str);
		if (errno == ENOENT)
			mkdir ("b_test_dir", my_mode);
		//free(err_str);
	} else {
		printf("error: %d\n", errno);
	}
}
