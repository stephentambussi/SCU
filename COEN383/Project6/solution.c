#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <assert.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/select.h>

#define BUFFER_SIZE 100
#define READ_END 0
#define WRITE_END 1
#define NUM_PIPES 5
#define PIPE_DURAITON 30

fd_set input, input_fd;
FILE *output;
char buffer[BUFFER_SIZE];
char consoleInput[BUFFER_SIZE-10]; // -10 to prevent compilation warning
int fd[NUM_PIPES][2];
int timeout = 0;
int messageCount = 1;
struct timeval start_t;
struct itimerval timer;
time_t start;

void readPipe(int *pd, int pipeEnd, int pipe)
{
    if (!timeout)
    {
        close(pd[WRITE_END]);               // close write end of pipe

        struct timeval currentTime;
        gettimeofday(&currentTime, NULL);     // populate timeval struct "currentTime"
        // Calculate current time stamp
        float currentReadTime = (float)((currentTime.tv_sec - start_t.tv_sec) + ((currentTime.tv_usec - start_t.tv_usec) / 1000000.));

        read(pipeEnd, buffer, BUFFER_SIZE); // read from pipe end into buffer (100 bytes)
        if (pipe == 4)
        {
            fprintf(output, "%6.3f: %s", currentReadTime, buffer);
        }
        else
        {
            fprintf(output, "%6.3f: %s\n", currentReadTime, buffer);
        }
    }
}

void writePipe(int *pd)
{
    if (!timeout)
    {
        close(pd[READ_END]);                        // close read end of pipe
        write(pd[WRITE_END], buffer, BUFFER_SIZE);  // write from buffer into pipe
    }
}

void interruptHandler(int signal)
{
    assert(signal == SIGALRM);
    timeout = 1;
    exit(0);
}

int main()
{
    output = fopen("output.txt", "w");     // open (or create if it doesn't exist) output.txt file

    time(&start);                          // get start time
    timer.it_value.tv_sec = PIPE_DURAITON; // 30 second timeout
    timer.it_value.tv_usec = 0;
    setitimer(ITIMER_REAL, &timer, NULL);
    gettimeofday(&start_t, NULL);
    signal(SIGALRM, interruptHandler);     // Once the timer reaches 30 seconds --> call interruptHandler to set timeout = 1
    srand(time(NULL));
    int seed;

    FD_ZERO(&input_fd);

    int i, pipeNumber;
    pid_t pid;

    for (i = 0; i < NUM_PIPES; i++)         // This will create 5 child processes and their associated pipes to the parent process
    {
        seed = rand();
        if (pipe(fd[i]) == -1)
        {
            perror("Pipe error");
            exit(1);
        }

        FD_SET(fd[i][READ_END], &input_fd);

        pid = fork();                       // Create child process
        if (pid == -1)
        {
            perror("Fork error");
            exit(1);
        }

        if (pid == 0)
        {
            fflush(stdout);
            // different child now has different random seed
            srand(seed);
            break;
        }
    }

    while (!timeout)
    {

        // Parent Process
        if (pid > 0)
        {
            input = input_fd;

            pipeNumber = select(FD_SETSIZE, &input, NULL, NULL, NULL);
            if (pipeNumber < 0)
            {
                perror("Pipe Number error");
                exit(1);
            }
            else if (pipeNumber == 0)
            {
                // should not be here, since the timeout parameter is NULL
                perror("Nothing to read");
            }
            else
            {
                for (i = 0; i < NUM_PIPES; i++)
                {
                    if (FD_ISSET(fd[i][READ_END], &input))
                    {
                        readPipe(fd[i], fd[i][READ_END], i);
                    }
                }
            }
        }
        // Child Process
        else
        { 
            input = input_fd;

            if (i == 4)
            {
                printf("Child 5 => ");
                fgets(consoleInput, BUFFER_SIZE, stdin);
                snprintf(buffer, BUFFER_SIZE, "Child 5: %s", consoleInput);
                writePipe(fd[i]);
            }
            else
            {
                snprintf(buffer, BUFFER_SIZE, "Child %d Message %d", i+1, messageCount++);
                writePipe(fd[i]);
                sleep(rand() % 3); // Each process sleeps for a random time (0, 1, or 2 seconds)
            }
        }
    }
    fclose(output);
    exit(0);
}