#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#define errno   (*_errno())

int main() {
	int current_id = getpid();
	int parent_id = getppid();
	
	char pathname[256];
	char arg1[14]= "----Hello----", arg2[14] ="----World----",arg4[15] = "$USER",arg3[10]= "----!----";
	
	char const *env[] = {"UserProfile = MyFirstUser","UserName = New_Avatar",NULL};
	pid_t pid; 
	int status;
	
	printf("Основная программа начала работу\n\n");
	
	
	printf("Введите полный путь до дочерней программы: ");
	scanf("%s",pathname);


	pid = fork();
	if (pid == 0) {
		
		int rv = execle(pathname,arg1,arg2,arg3,NULL,env);
		if (rv == -1){
			perror("ExecError occured");
			return 0;
			}
		
	}
	else if (pid > 0) {
		printf("\nКод родительского процесса: %d\n", parent_id);
		printf("Код текущего процесса: %d\n", current_id);
		printf("Код дочернего процесса: %d\n\n", pid);
		
		while (waitpid(pid,&status,WNOHANG) == 0) {
			printf("Waiting...\n");
			fflush(stdout);

			usleep(500000);
			}
			
		printf("\nДочерний процесс завершился с кодом %d\n",status);
		printf("Основная программа закончила работу\n");
	}
	else{
		perror("ForkError");
	}

	return 0;
};
