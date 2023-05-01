#include <sys/types.h>
#include <utime.h>
#include <stdlib.h>
#include<stdio.h>

     



int main(){
	struct utimbuf my_time_buff;
	FILE *fp;
	char filename[256];
	int rv;
	my_time_buff.actime = 10;
	my_time_buff.modtime = 10;
	
	printf("Введите имя файла, к которому хотите изменить время доступа: ");
	scanf("%s",filename);
	if ((fp = fopen(filename,"r")) == NULL){
		perror("FileError: ");
		return 0;
	}
	else{
		printf("%s\n",filename);
	}
	fclose(fp);

	if (utime(filename,&my_time_buff) == 0){
		printf("All success ");
		
		}
	else{
		perror("Error by seting time: ");
		}	
	return 0;
}
