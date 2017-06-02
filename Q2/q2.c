#include "csapp.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
	int i = 0, j, status;
	FILE* pfilename;
	pid_t pid;
	char buf[128];
	char input[128];

	while(fgets(input, sizeof(input), stdin) != NULL ){
		if (Fork() == 0) {
			sprintf(buf, "gzip -d %s", input);
			system(buf);
			exit(1);
		}
		i++;
	}
	
	for(j=0; j < i; j++) {
		pid = wait(&status);
	}
	
	printf("It's Done!\n");
	exit(0);
}
