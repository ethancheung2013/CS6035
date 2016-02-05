#include <stdio.h>
#include <string.h>

// crashes with the following (24bytes)
//12345678123456781234

int main(int argc, char *argv[]){
    char buffer[8];
    strcpy(buffer,argv[1]);
};

