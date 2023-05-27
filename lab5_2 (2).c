#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <fstream>
#include <fcntl.h>           
#include <sys/stat.h>        
#include <semaphore.h>
#include <fcntl.h>
#include <cstring>
#include <signal.h>
#include < time.h >
using namespace std;

void sig_handler(int signo) {
	cout << "get SIGPIPE\n";
}

int flag_write = 0, flag_open = 0, fd;
const int size = 2;
long buffer[size];
string buf;
const char* pathname = "/tmp/my_named_pipe";
pthread_t id1, id2;


static void* write(void* args) {
	cout << "\nПоток write начал работу.\n";
	fd = open("/tmp/my_named_pipe", O_WRONLY | O_NONBLOCK);
	struct timespec res_clock;
	
	

	
	while (flag_write == 0) {
		clock_getres(clockid_t clk_id, &res_clock);
		buffer[0] = res_clock
		int error = write(fd, buffer, size);
		if (error == -1) {
			perror("write");
			sleep(1);
		} if (error > 0) {
			perror("Write");
			sleep(1);
		}
	}
	cout << "\nПоток FIFO закончил работу.\n";
	pthread_exit((void*)4);
}

static void* open(void* args) {
	cout << "\nПоток open начал работу.\n";
	int error = 0;
	while (flag_open == 0) {
		error = open(pathname, O_WRONLY | O_NONBLOCK);
		if (error == -1) {
			perror("\n");
			sleep(1);
		}
		else {
			cout << "\nЗашёл для создания.\n";
			pthread_t id2;
			pthread_create(&id2, NULL, &write, NULL);
			flag_open = 1;
		}
	}

	cout << "\nПоток open закончил работу.\n";
	pthread_exit((void*)3);
}

int main() {
	signal(SIGPIPE, sig_handler);
	cout << "Программа начала работу.\n";
	fd = mkfifo(pathname, 0777);

	pthread_create(&id1, NULL, &open, NULL);
	cout << "\nПрограмма ждёт нажатия клавиши.\n";
	getchar();
	cout << "\nКлавиша нажата.\n";
	flag_write = 1;
	flag_open = 1;
	pthread_join(id1, NULL);
	pthread_join(id2, NULL);
	close(fd);
	unlink(pathname);
	cout << "\nПрограмма завершила работу.\n";
}
