#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#define BUFF_SIZE 256
#define blue() printf("\033[0;34m")
#define reset() printf("\033[0m")
#define green() printf("\033[0m")
#define bold() printf("\e[1m")
#define boldOff() printf("\e[m")



char* getInputFromUser();

char** splitArgument(char*);

void getLocation();