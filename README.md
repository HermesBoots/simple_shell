# Title: simple_shell

## Description

simple_shell is our attempt to recreate a basic shell to communicate with the
operating system. We are using the C programing language to write all our
sourcecode.

### Built-ins

`cd`

Changes the working directory. This affects relative path names typed on the command line.

Example usage: `$ cd /usr/bin`

`env`

Prints a list of environment variables currently used by the shell.

Example usage: `$ env`

`exit`

With no arguments, exits the shell with the status of the previous command. With a numeric argumet, exits with the given status code.

Example usage: `$ exit`

`help`

Prints out explanation on how to use built-in commands.

Example usage: `$ help cd` 

`setenv`

Adds environment variables or changes their values.

Example: `$ setenv Test this/is/a/path`

`unsetenv`

Deteles environment variables in the shell.

Example usage: `$ unsetenv Test`

## Installation

To instal our shell, clone the repository and run your C compiler of choice.
We have been using [GCC](https://gcc.gnu.org). If using GCC:
`gcc -Wall -Werror -Wextra -pedantic *.c -o hsh`
inside the repository will create the `hsh` file to run our shell.

## Usage

To start our shell, run the file you compiled. In our case, that would be `hsh`.
So `./hsh` will start our shell. Now type in a command like `/bin/ls`.
```
672@ubuntu:~/shell$ ./shell
($) /bin/ls
```
You should get a listing of all the files in your current directory.

## Bugs

Feel free to messege either of the authors when a bug is found. We
may go back and fix it!

## Authors
Sam Hermes: *HermesBoots*

[Kyle Litscher](https://github.com/klitscher) | [LinkedIn](https://www.linkedin.com/in/kylelitscher/) | [Twitter](https://twitter.com/Coding_KGL)
