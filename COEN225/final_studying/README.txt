- around 10 questions on final 
   - 3 questions from midterm 1 and 2 concepts
   - 7 questions from after midterm 2 concepts

FROM LECTURE 8
1.3.3 Study questions:
a) how many processes if we add another fork call to fork2.c
   
   @ 8 processes are created in total -- 3 fork calls = 8 processes

b) how can we modify forkipc.c (shared_mem.c) such that parent process places a string in shared memory 
   for child process to convert to upper case, in the same shared memory

   @ See shared_mem_mod.c

c) if both parent and child processes are sleeping for 100 seconds and parent is killed,
   what becomes the new parent of the child process
   
   @ Child process becomes what is known as a 'orphan process' and it is adopted by the 'init process'
   which is the first process to start when the computer boots up.

d) modify newshell.c such that if the entered command returns a non zero code, the newshell will terminate.
   For instance, if you enter the cat command below and the file xyz does not exist, the return code is non zero.
   $ cat xyz
   cat: xyz: No such file or directory
   $ echo $?
   1

   @ See newshell_mod.c

1.4.1 Study questions:
Write a program that passes 3 parameters like "xyz", 12, 0.5 to a child thread
and have it compute a string being "xyz"*(int)12*0.5 = "xyzxyzxyzxyzxyzxyz" and 
return it.

   @ See thread_str_compute.c

FROM LECTURE 9
1.2.1 Study questions:
Fix deadlock.c so they no longer have deadlocks.

   @ See deadlock_fixed.c

1.2.2 Study questions:
a) Given file locking information from the lslocks command,
   enter them into the detect deadlock program, and show deadlock cycle in DFS order.

   @@@@@@@@@@@@@@@@@@@@@@@@@@@
   Input:
      process1 file1 file2 *file3      [process1]->[file3]     proc1 waits for file3
      process2 file3 *file1            [process2]->[file1]     proc2 waits for file1
   Output:
      dfs(1)
      proc 1 has file1 file2 and waits for resource: file3 held by proc 2
      dfs(2)
      proc 2 has file3 and waits for resource: file1 held by proc 1
      dfs(1)
      Deadlock detected, pid = 1

b) Enhance the detect deadlock program to find all deadlocks, not just the first one.
   Fix can be done in the check_deadlock function.

   @@@@@@@@@@@@@@@@@@@@@@@@@@@ See DetectDeadlocks.c
   Changes:
      in check_deadlock(), change "if(dfs(i)) then exit(0)" to "if(!dfs(i)) then exit(0)"
   Input:
      process1 file1 file2 *file3      [process1]->[file3]     proc1 waits for file3
      process2 file3 *file1            [process2]->[file1]     proc2 waits for file1
      process3 file4 *file2            [process3]->[file2]     proc2 waits for file2
   Output:
      dfs(1)
      proc 1 has file1 file2 and waits for resource: file3 held by proc 2
      dfs(2)
      proc 2 has file3 and waits for resource: file1 held by proc 1
      dfs(1)
      Deadlock detected, pid = 1
      Deadlock pid: 2
      Deadlock pid: 1
      dfs(3)
      proc 3 has file4 and waits for resource: file2 held by proc 1
      dfs(1)
      Deadlock detected, pid = 1
      Deadlock pid: 3

c) FileLockingApp.c can only lock one file, then it is blocked.
   Can you modify it so it can lock 2 files?

   @ See FileLockingApp.c (can lock more than 2 files)

2.5.3 Study questions:
Given a SIMPLE program WITHOUT loops, indicate all code paths.

2.5.4 Study questions:
Write a small program with a buffer overflow vulnerability.
Compile it using AFL-GCC.
Fuzz it using AFL-FUZZ for one hour.
Report numbers of the crashing and hanging test cases.
Try the test cases out and see if they indeed produce the crashes or hangs.

   @ See afl_buffer_overflow.c
   @ 11 unique crashes
   @ 0 hanging test cases


FROM LECTURE 10
2. Study question:
Given a program with runtime vulnerabilities, indicate which ones can/cannot be detected by Valgrind/Google Sanitizer.

3. Study questions:
Given a program, identify the vulnerabilities, and which analysis solution is used to detect the vulnerabilities.
Given a tainted program, provide malicious input to inject a command.