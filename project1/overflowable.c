
#include <stdio.h>
#include <strings.h>

void bad_function(){
	char buffer[12];
	printf("please enter your name\n");
	gets(buffer);
}

int main(int argc, char *argv[]){
	bad_function();
};