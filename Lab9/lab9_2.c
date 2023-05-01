#include <sys/types.h>
#include <utime.h>
#include <stdlib.h>
#include<stdio.h>
#include <sys/capability.h>
cap_t cap_get_file(const char *path_p);
char *cap_to_text(cap_t caps, ssize_t * length_p);

cap_t cap_lab91;
char* text_cap;
ssize_t length;
const char * ppath = "./lab9_1";

int main(){



cap_lab91 = cap_get_file(ppath);

text_cap = cap_to_text(cap_lab91,&length);

printf("\"%s\"\n%ln",text_cap,&length);





return 0;
};
