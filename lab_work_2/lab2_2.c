#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

typedef struct {
	int flag1;
	int flag2;
	sem_t sem;
	
}targs;

void* proc1(void *arg){

	targs *args = (targs*)arg;
	
	printf("\nПоток 1 начал работу\n");

	while(args->flag1 == 0){
		
		int rv = sem_trywait(&args->sem);
		
		if(rv == -1){
			sleep(1);
			}
			
		for(int i =0; i<10; i++){
		
		
			putchar('1');
			fflush(stdout);
			sleep(1);
		}
		
		sem_post(&args->sem);
		
		sleep(1);
		}
		
		
	pthread_exit((void*)1);
		
}
 
void* proc2(void *arg){

	targs *args = (targs*)arg;
	
	printf("\nПоток 2 начал работу\n");
	
	
	while(args->flag2 == 0){
	
		int rv = sem_trywait(&args->sem);
		
		if(rv == -1){
		
			sleep(1);
			
			}
			
		
		for(int i =0; i<10; i++){
		
			putchar('2');
			fflush(stdout);
			sleep(1);
		}
		
		sem_post(&args->sem);
		
		sleep(1);
		}
		
		
	pthread_exit((void*)2);
}
 
int main(){
	
	targs arg;
	arg.flag1 = 0;
	arg.flag2 = 0;
	
	pthread_t id1;
	pthread_t id2;
	
	int *exitcode;
	
	
	
	
	sem_init(&arg.sem,0,1);
	
	printf("Программа начала работу\n");
	printf("\nДля завершения работы нажмите Enter\n");
	
	pthread_create(&id1,NULL,proc1,&arg);
	pthread_create(&id2,NULL,proc2,&arg);
	
	
	
	
	getchar();
	
	arg.flag1 = 1;
	arg.flag2 = 1;
	
	printf("\nКлавиша Enter нажата \nОжидание завершения потоков...\n ");
	
	
	pthread_join(id1,(void**)&exitcode);
	printf("\nПоток 1 завершен с кодом %p\n",exitcode);
	
	pthread_join(id2,(void**)&exitcode);
	printf("\nПоток 2 завершен с кодом %p\n",exitcode);
	
	printf("\nПрограмма завершила работу\n");
	
	sem_destroy(&arg.sem);

	
	return 0;
	
	
}	
	
	
