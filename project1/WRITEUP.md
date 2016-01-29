
#Task 1
###Task 1.1 Vulnerable Program (5 points)
The initial task was to write a C/C++ program that contains a stack buffer overflow vulnerability. ```overflowable.c``` detailed below contains a vulnerability since it utilizes the vulnerable and depreceated ```gets()``` command.  This command does not check the size of the input against the size of what the buffer is.
######overflowable.c

```c
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
```
#####Compile Instructions
```sh
$ gcc overflowable.c -o overflowable -fno-stack-protector
```

####Task 1.2 Stack Layout (25 points)
Note: the stack layout should contain the following contents:
- Stack layout (5 points)
- High and low address of stack, stack grows direction (5 points)
- Size of each part on the stack (5 points)
- Content of each part of the stack (5 points)
- Overflowed area of the stack (5 points)


| Addresses    |   | Contents           |
|---------|---|-----------------------------|
| Addr    |   | <- argc (4 bytes)           |
| Addr_4  |   | <- argv (4 bytes)           |
| Addr_8  |   | <- return address (4 bytes) |
| Addr_12 |   | start buffer (12 bytes)     |
|         |   | ...                         |
| Addr_   |   | end buffer (12 bytes)       |


# Task 2:

###Task 2.1 Buffer overflow detection data craft and overflow proof in GDB (10 points)
###Task 2.2. Locate system() address in GDB (10 points)
###Task 2.3. Locate /bin/sh address in GDB(10 points)
###Task 2.4. Correct exploit payload in data.txt and being able to open the shell in terminal(30
points)
4
