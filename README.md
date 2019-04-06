#Title: simple_shell

##Description

simple_shell is our attempt to recreate a basic shell to communicate with the
operating system. We are using the C programing language to write all our
sourcecode.

###Features

1. Accept commands from the command line
2. Execute simple commands
3. Handle errors
4. Handle comand line arguments
5. Handle PATH
6. EXIT
7. Can print current environment

Basically, we want to replicate the basic features of /bin/sh

##Installation

To instal our shell, clone the repository and run your C compiler of choice.
We have been using [GCC](https://gcc.gnu.org). If using GCC:
'gcc -Wall -Werror -Wextra -pedantic *.c -o hsh'
inside the repository will create the 'hsh' file to run our shell.

##Usage

To start our shell, run the file you compiled. In our case, that would be 'hsh'.
So './hsh' will start our shell. Now type in a command like '/bin/ls'.
'672@ubuntu:~/shell$ ./shell'
'($) /bin/ls'
You should get a listing of all the files in your current directory.

##Bugs

Many many bugs! This was a learning exercise, so expect things to not work or
break. Feel free to messege either of the authors when a bug is found. We
may go back and fix it!

##Authors
Sam Hermes *HermesBoots*
Kyle Litscher *klitscher*