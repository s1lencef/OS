#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>


int main(int argc, char *argv[]){
	int parent_id, current_id,k =0 ;
	printf("Дочерний процесс начал работу\n");
	for (int i = 0; i<argc;i++){
		printf("\n%s\n", argv[i]);
		fflush(stdout);

		sleep(1);
	}
	printf("\nНовые переменные среды:\n");
	while(environ[k]){
		printf("\t%s\n",environ[k]);
		k++;
	}
	parent_id = getppid();
	current_id = getpid();
	
	printf("\nКод родительского процесса: %d\n", parent_id);
	printf("Код текущего процесса: %d\n", current_id);
	
	exit(4);
}

