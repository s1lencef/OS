#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <fstream>
#include <fcntl.h>           
#include <sys/stat.h>        
#include <semaphore.h>
#include <fcntl.h>
#include <cstring>
#include < time.h >
using namespace std;

int flag_read = 0, fd;

int buffer[2];
const char* pathname = "/tmp/my_named_pipe";
pthread_t id1;

static void* read(void* args) {
	cout << "\nПоток read начал работу.\n";
	int size = 0;
	int error = 0;
	while (flag_read == 0) {
		memset(buffer, 0, 2);
		error = read(fd, &buffer, 2);
		if (error == -1) {
			perror("read");
			sleep(1);
		}
		else if (error > 0) {
			perror("");
			cout << "\n: " << buffer[0] << "\n";
			fflush(stdout);
			sleep(1);
		}
	}

	cout << "\nПоток READ закончил работу.\n";
	pthread_exit((void*)4);
}

int main() {
	cout << "Программа начала работу.\n";
	fd = mkfifo(pathname, 0777);

	pthread_t id1;
	fd = open(pathname, O_RDONLY | O_NONBLOCK);
	pthread_create(&id1, NULL, &read, NULL);
	cout << "\nПрограмма ждёт нажатия клавиши.\n";
	getchar();
	cout << "\nКлавиша нажата.\n";
	flag_read = 1;
	pthread_join(id1, NULL);
	close(fd);
	unlink(pathname);
	cout << "\nПрограмма завершила работу.\n";
}
