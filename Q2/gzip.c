#include "csapp.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv, char **envp) {
        int i, status;
        FILE* pfilename;
        pid_t pid;
        char buf[128];

        for(i=1; argv[i]; i++) {
                if (Fork() == 0) {
                        sprintf(buf, "gzip -d %s", argv[i]);
                        system(buf);
                        exit(1);
                }
        }

        while ((pid = waitpid(-1, &status, 0)) > 0) {
                if(WIFEXITED(status)) ;
        }

        printf("It's Done!\n");
        exit(0);
}

