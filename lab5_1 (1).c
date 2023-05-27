#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

#define PIPE "/tmp/my_pipe"

int exit_flag = 0;
int fd;
void *process(void *arg)
{
	char buf[256];
	while(1){
		if (read(fd, buf, sizeof(buf) - 1) != 0 || exit_flag == 1)
			break;
		printf ("Ожидание программы 2\n");
		sleep(1);
	}
    int n;
    while(exit_flag == 0){
    	n = read(fd, buf, sizeof(buf) - 1);
        if (n == -1) {
        	if (errno != EAGAIN){
	            perror("read");
	            break;
        	}
        }
        else if (n == 0){
			printf ("Программа 2 завершила работу\n");
			printf ("Нажмите клавишу, чтобы завершить программу 1\n");
			break;
		}
		else {
            printf("Получено сообщение: %s\n", buf);
        }
    	sleep(1);
	}	
}
int main()
{	
    printf ("Программа 1 начала работу\n");
    
   	mkfifo(PIPE, 0666);
   	fd = open(PIPE, O_RDONLY | O_NONBLOCK);
   	if (fd == -1) {
        perror("open");
        return 1;
    }
    pthread_t thread;
    pthread_create(&thread, NULL, process, NULL);
    printf("Для завершения нажмите любую клавишу и после Enter!\n");
    getchar();
	printf("Клавиша была нажата!\n");
    exit_flag = 1;
    pthread_join(thread, NULL);
	close(fd);
    unlink(PIPE);
   	
	printf ("Программа 1 завершила работу\n");
    return 0;
}
