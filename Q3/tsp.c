#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int m[17][17] ;

int path[17] ;
int used[17] ;
int length = 0 ;
int min = -1 ;
pid_t tmp;

void handler(int signum) {
	int s;
	
	if(tmp != getpid()) {
		kill(getpid(), SIGINT);
		wait(&s);
		exit(1);
	}
}

void _travel(int idx) {
	char buf[128];

        sprintf(buf, "%d.sol", getpid());

        FILE * out;

	int i ;

	if (idx == 17) {
		if (min == -1 || min > length) {
			out = fopen(buf, "w");
			min = length ;
			fprintf(out, "%d (", length) ;
			for (i = 0 ; i < 16 ; i++) 
				fprintf(out, "%d ", path[i]) ;
			fprintf(out, "%d)\n", path[16]) ;
			fclose(out);
		}
	}
	else {
		for (i = 0 ; i < 17 ; i++) {
			if (used[i] == 0) {
				path[idx] = i ;
				used[i] = 1 ;
				length += m[path[idx-1]][i] ;
				_travel(idx+1) ;
				length -= m[path[idx-1]][i] ;
				used[i] = 0 ;
			}
		}
	}
}

void travel(int start) {
	path[0] = start ;
	used[start] = 1 ;
	_travel(1) ;
	used[start] = 0 ;
}

int main() {
	int i, j, t, status, min_l = 9999;
	pid_t pid ;
	char buf[128];
	int num[17];
	char c;
	int len;
	
	tmp = getpid();

	signal(SIGINT, handler);

	FILE * fp = fopen("gr17.tsp", "r") ;

	for (i = 0 ; i < 17 ; i++) {
		for (j = 0 ; j < 17 ; j++) {
			fscanf(fp, "%d", &t) ;
			m[i][j] = t ;
		}
	}
	fclose(fp) ;

	for (i = 0 ; i < 17 ; i++) {
		if((pid = fork()) == 0){
			travel(i) ;
			exit(1);
		}
	}

	for (i = 0 ; i<17; i++) {
		wait(&status);
	}

	i = 1;

	FILE * in;

	do {
		sprintf(buf, "%d.sol", getpid()+i);
		in = fopen(buf, "r");
		fscanf(in, " %d", &len);
		if(min_l > len) {
			min_l = len;
			fscanf(in, " %c", &c);
			for ( j = 0; j < 17; j++) {
				fscanf(in, " %d", &num[j]);
			}
		}
		fclose(in);
		i++;
	}while(i <= 17);

	printf("\n%d (", min_l) ;
	for (i = 0 ; i < 16 ; i++)
		printf("%d ", num[i]) ;
	printf("%d)\n", num[16]) ;

	exit(0);
}
