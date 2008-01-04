#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cctype>


int main(int argc, char* argv[]){
	int c;
	char default_work_dir[]="xtcc_work";
	char * work_dir=default_work_dir;
	opterr=1;
	while((c=getopt(argc, argv, "w:"))!=-1){
		switch(c){
			case 'w':
				work_dir=optarg;
			break;
			case '?':
				if (optopt == 'w')
					fprintf (stderr, "Option -%c requires an argument.\n", optopt);
				else if (isprint (optopt))
					fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				else
					fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
				exit(1);
			break;	
			default:
				exit(1);
		}
	}
	printf("work dir set to %s\n", work_dir);
	if(argc-optind<2){
		printf("Usage: xtcc -w workdir <inp-file> <data-file>\n");
	}
	for(int i=optind; i<argc;++i){
		printf("Non-option arg %s\n", argv[i]);
	}
	return 0;
}
