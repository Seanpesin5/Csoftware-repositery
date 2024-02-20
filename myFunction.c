#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h> // For getenv if userLogin doesnt work

#define BUFF_SIZE PATH_MAX
#define HOST_NAME_MAX 255

void bold() {
    printf("\033[1m");
}

void blue() {
    printf("\033[34m");
}

void green() {
    printf("\033[32m");
}

void reset() {
    printf("\033[0m");
}

void getLocation() {
    char location[BUFF_SIZE];
    char computerName[HOST_NAME_MAX];
    char *userName = getlogin(); // Try to get the username using getlogin()

    // If getlogin() returns NULL, try to get the username using getenv("USER")
    if (userName == NULL) {
        userName = getenv("USER");
    }

    if (getcwd(location, BUFF_SIZE) == NULL) {  //get current work directory
        puts("Error");
        return;
    }
    
    struct utsname unameData; // gets customable data from the
    
    if(uname(&unameData) != 0) {
        puts("Error getting computer name");
        return;
    }
    strcpy(computerName, unameData.nodename);// copying the string from src to destination

    bold();
    green(); // Change color to green for username
    printf("%s@", userName);
    reset();
    green(); // Change color to green for computer name
    printf("%s:", computerName);
    reset();
    blue(); // Change color to blue for path
    printf("%s$ ", location);
    reset();
}