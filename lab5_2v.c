#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>
#include <signal.h>
#include <time.h>

#define PIPE "/tmp/my_pipe"

int exit_flag = 0;
int fd;
void sig_handler(int signo) {
	printf("Программа 1 завершилась\n");
	printf ("Нажмите клавишу, чтобы завершить программу\n");
    exit_flag = 1;
}
void *process(void *arg)
{
	while(1)
	{
	   	fd = open(PIPE, O_WRONLY | O_NONBLOCK);
	   	if (fd != -1 || exit_flag == 1)
	   		break;
	   	printf ("Ожидание программы 1\n");
		sleep(1);
	}
    struct timespec res_clock;
    clock_getres(CLOCK_REALTIME, &res_clock);
    while(exit_flag == 0)
	{
        if (write(fd, &res_clock, sizeof(res_clock)) == -1) {
        	if (exit_flag == 1){
			    break;
			}
            perror("write");
        }
        printf("Отправлено сообщение: %ld\n", res_clock.tv_nsec);
    	sleep(1);
	}	
}
int main()
{	
    printf ("Программа 2 начала работу\n");
    
   	mkfifo(PIPE, 0666);
   	signal(SIGPIPE, sig_handler);
    pthread_t thread;
    pthread_create(&thread, NULL, process, NULL);
    printf("Для завершения нажмите любую клавишу и после Enter!\n");
    getchar();
	printf("Клавиша была нажата!\n");
    exit_flag = 1;
    pthread_join(thread, NULL);
	close(fd);
    unlink(PIPE);
   	
	printf ("Программа 2 завершила работу\n");
    return 0;
}
