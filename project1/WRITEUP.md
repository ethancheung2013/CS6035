
#Task 1
###Task 1.1 Vulnerable Program (5 points)
The initial task was to write a C/C++ program that contains a stack buffer overflow vulnerability. ```overflowable.c``` detailed below contains a vulnerability since it utilizes the vulnerable and depreceated ```gets()``` command.  This command does not check the size of the input against the size of what the buffer is.
######overflowable.c

```c
#include <stdio.h>
#include <strings.h>

int main(int argc, char *argv[]){
    char buffer[8];
    strcpy(buffer,argv[1]);
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

#####Prior to overflow:

![http://imgur.com/a/JoZV8](http://i.imgur.com/BxQlUpF.jpg)

#####After overflow: (to show overflowed area of the stack)

![http://imgur.com/a/JoZV8](http://i.imgur.com/h3S1iXe.jpg)

###Task 1.3 Exploiting Explanation (10 points)

To exploit the stack we must first figure out how to cause the program to crash.  It is easy to do this by inputing the following test procedures:

![crashing the program]()

After causing the program to crash, you must then try to find what the proper input to completely overide the return address.  I accomplished this by adding ```0``` onto the tail of my input.  The result from running the program should be something like ```Program received signal SIGSEGV, Segmentation fault. 0x30303030 in ?? ()```.  The reason that we are looking for ```0x30303030``` is the in ```ASCII``` the hex for ```0``` is ```30``` and we are looking for all 4.  The Steps below show how to accomplish this:

![crafting your input]()


# Task 2:

###Task 2.1 Buffer overflow detection data craft and overflow proof in GDB (10 points)
###Task 2.2. Locate system() address in GDB (10 points)
###Task 2.3. Locate /bin/sh address in GDB(10 points)
###Task 2.4. Correct exploit payload in data.txt and being able to open the shell in terminal(30
points)
4
