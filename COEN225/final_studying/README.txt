1.3.3 Study questions:
a. how many procesess if we add another fork call to fork2.c
b. how can we modify forkipc.c such that parent process places a string in shared memory 
   for child process to convert to upper case, in the same shared memory
c. if both parent and child processes are sleeping for 100 seconds and parent is killed,
   what becomes the new parent of the child process
d. modify newshell.c such that if the entered command returns a non zero code, the newshell will terminate.
   For instance, if you enter the cat command below and the file xyz does not exist, the return code is non zero.
   $ cat xyz
   cat: xyz: No such file or directory
   $ echo $?
   1

1.4.1 Study questions:
Write a program that passes 3 parameters like "xyz", 12, 0.5 to a child thread
and have it compute a string being "xyz"*(int)12*1.5 = "xyzxyzxyzxyzxyzxyz" and 
return it.