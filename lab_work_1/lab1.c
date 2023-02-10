#include <stdio.h>
#include <pthread.h>
#include <unistd.h>



void* proc1(void *arg){

	int *flag = (int*)arg;
	
	printf("\nПоток 1 начал работу\n");
	
	
	while(*flag == 0){
		printf("%d\n",1);
		sleep(1);
		}
		
		
	pthread_exit((void*)1);
		
}
 
void* proc2(void *arg){

	int *flag = (int*)arg;
	
	printf("\nПоток 2 начал работу\n");
	
	
	while(*flag == 0){
		printf("%d\n",2);
		sleep(1);
		}
		
		
	pthread_exit((void*)2);
}
 
int main(){

	int flag1 = 0;
	int flag2 = 0;
	int *exitcode;
	
	pthread_t id1;
	pthread_t id2;
	
	
	printf("Программа начала работу\n");
	printf("\nДля завершения работы нажмите Enter\n");
	
	pthread_create(&id1,NULL,proc1,&flag1);
	pthread_create(&id2,NULL,proc2,&flag2);
	
	
	
	
	getchar();
	
	printf("\nКлавиша Enter нажата \n");
	
	flag1 = 1;
	flag2 = 1;
	
	pthread_join(id1,(void**)&exitcode);
	printf("\nПоток 1 завершен с кодом %p\n",exitcode);
	
	pthread_join(id2,(void**)&exitcode);
	printf("\nПоток 2 завершен с кодом %p\n",exitcode);
	
	printf("\nПрограмма завершила работу\n");
	
	
	return 0;
	
	
}	
	
	
