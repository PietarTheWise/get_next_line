<h1 align="center">
  <br>
    get_next_line
  <br>
</h1>

<h3 align="center">A handy tool for parsing files.</h3>

<p> </p>

<p align="center">
  
</p>

<p align="center">
  <a href="#what-does-it-do">What does it do?</a> •
  <a href="#how-to-use">How To Use</a> •
  <a href="#disclaimer">Disclaimer</a>
</p>

## What does it do?

* Reads a single line from file descriptor until newline ("\n") character is found.
* Dynamically allocates and stores the read line into a char ** pointer given as the function's input 
* By calling the function again, the function returns the next line on the given file.
* By calling the function n times the function loops across the file n lines storing always next line to the pointer
* Returns 1 if file has been read, 0 if we have reached end of the file and -1 if there is an error.
* Can be called with multiple file descriptors.

## How To Use

To clone and run this application, you'll need [Git](https://git-scm.com) and gcc compiler installed on your computer. This has been tested only on MacOs and linux. Run the following commands on the command line:

```bash
# Clone this repository
$ git clone https://github.com/PietarTheWise/get_next_line.git
# Build the libft library by entering following lines to the console:
$ cd libft/
$ make
# if working on linux, remove -I in the makefile on line 29

#To test it create two files
$ touch test.txt && touch main.c

#Write some lines to test.txt. You can use editor or you can run the following on terminal
$ echo read 1 >> test.txt && echo read 2 >> test.txt && echo read 3 >> test.txt && echo read 4 >> test.txt && echo read 5 >> test.txt
```

```c
// add the following on the main.c file:
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	int		fd;
	int		i;
	char	*str;

	fd = open(argv[1], O_RDONLY);
	i = 0;
	while (i < 5)
	{
		get_next_line(fd, &str);
		printf("%s\n", str);
		free(str);
		i++;
	}
  return (0);
}

```
```bash
#Build the program using the following
$ gcc main.c get_next_line.c get_next_line.h libft/libft.a
#Run the program
$ ./a.out test.txt
```

## DISCLAIMER

<p>
This is a project from the 42 school, which is a school that utilizes peer to peer learning.
We're only given a document that gives us the details of the assignment, therefore each implementation
is unique. Each assignment is tested for crashes and other bugs thoroughly by other peers. Apart from some exceptions, existing
libraries are banned, these projects utilize our self made version of libc called libft.
</p>
