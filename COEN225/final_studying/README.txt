- around 10 questions on final 
   - 3 questions from midterm 1 and 2 concepts
   - 7 questions from after midterm 2 concepts

FROM LECTURE 8
1.3.3 Study questions:
a) how many procesess if we add another fork call to fork2.c
b) how can we modify forkipc.c such that parent process places a string in shared memory 
   for child process to convert to upper case, in the same shared memory
c) if both parent and child processes are sleeping for 100 seconds and parent is killed,
   what becomes the new parent of the child process
d) modify newshell.c such that if the entered command returns a non zero code, the newshell will terminate.
   For instance, if you enter the cat command below and the file xyz does not exist, the return code is non zero.
   $ cat xyz
   cat: xyz: No such file or directory
   $ echo $?
   1

1.4.1 Study questions:
Write a program that passes 3 parameters like "xyz", 12, 0.5 to a child thread
and have it compute a string being "xyz"*(int)12*1.5 = "xyzxyzxyzxyzxyzxyz" and 
return it.

FROM LECTURE 9
1.2.1 Study questions:
Fix deadlock.c so they no longer have deadlocks.

1.2.2 Study questions:
a) Given file locking information from the lslocks command,
   enter them into the detect deadlock program, and show deadlock cycle in DFS order.
b) Enhance the detect deadlock program to find all deadlocks, not just the first one.
   Fix can be done in the check_deadlock function.
c) FileLockingAppl.c can only lock one file, then it is blocked.
   Can you modify it so it can lock 2 files?

2.5.3 Study questions:
Given a SIMPLE program WITHOUT loops, indicate all code paths.

2.5.4 Study questions: NEED TO INSTALL AFL ON VM
Write a small program with a buffer overflow vulnerability.
Compile it using AFL-GCC.
Fuzz it using AFL-FUZZ for one hour.
Report numbers of the crashing and hanging test cases.
Try the test cases out and see if they indeed produce the crashes or hangs.

FROM LECTURE 10
2. Study question:
Given a program with runtime vulnerabilities, indicate which ones can/cannot be detected by Valgrind/Google Sanitizer.

3. Study questions:
Given a program, identify the vulnerabilities, and which analysis solution is used to detect the vulnerabilities.
Given a tainted program, provide malicious input to inject a command.