/* Name: Stephen Tambussi
 * Date: 5/20/2021
 * Title: Lab 8 - Memory management
 * Description: This program simulates page replacement algorithms.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct {//to 
    int pageno;
    int time; //for lru -- amount of time a page has spent in queue
    int flag; //for second chance
} ref_page;


int main(int argc, char *argv[])
{
    printf("Command line format: $program_name <cache size> <selection> \n");
    printf("1: FIFO     2: LRU      3: Second chance \n");
    if(argc < 3)
    {
        printf("Incorrect number of command line arguments. \n");
        return 0;
    }
    int C_SIZE = atoi(argv[1]); // Size of Cache passed by user 
    int selection = atoi(argv[2]); //To select the page replacement algorithm
    ref_page cache[C_SIZE]; // Cache that stores pages 
    char pageCache[100]; // Cache that holds the input from test file
    int counter = 0; //keeps track of first item in queue for FIFO
    int i, j, temp, oldest;
    int replace = 0;
    int numRequests = 0; //keeps track of total memory requests
    int totalFaults = 0; // keeps track of the total page faults
    
    for (i = 0; i < C_SIZE; i++){//initialise cache array  
         cache[i].pageno = -1;
         cache[i].time = 1;
         cache[i].flag = 0;
    }

    while (fgets(pageCache, 100, stdin)){
        numRequests++;
    	int page_num = atoi(pageCache); // Stores number read from file as an int
        if(selection == 1) //FIFO
        {
            bool foundInCache = false;
            for(i = 0; i < C_SIZE; i++)
            {
                if(cache[i].pageno == page_num) //requested page is in cache
                {
                    foundInCache = true; //set variable to true
                    break;
                }
            }
            if(foundInCache == false)
            {
                printf("Page fault at page %d \n", page_num); //print out page where fault occurred
                cache[counter].pageno = page_num; //replace old page at front of queue with new page
                totalFaults++; //increase total faults
                counter = (counter + 1) % C_SIZE; //so counter never goes out of bounds
            }
        }
        else if(selection == 2) //LRU - Least Recently Used
        {
            bool foundInCache = false;
            for(i = 0; i < C_SIZE; i++)
            {
                temp = 0;
                oldest = cache[i].time; //set oldest page to current index (i) page
                if(cache[i].pageno == page_num) //if page is found
                {
                    for(j = 0; j < C_SIZE; j++)
                    {
                        if(cache[j].time < cache[i].time) //pages that are younger than target(i) in queue are time increased since they haven't been accessed
                            cache[j].time++;
                    }
                    foundInCache = true;
                    cache[i].time = 0; //set time to 0 since this page was found in cache and therefore "used"
                    break;
                }
                for(j = 0; j < C_SIZE; j++) //increment each pages time in queue since they have not been "used"
                    cache[j].time++;
            }
            if(foundInCache == false) 
            {
                for(j = 0; j < C_SIZE; j++)
                {
                    if(oldest < cache[j].time)//find oldest page (least recently used) in queue
                    {
                        temp = j;
                        oldest = cache[j].time;
                    }
                }
                printf("Page fault at page %d \n", page_num);
                cache[temp].pageno = page_num; //replace oldest page with new page
                cache[temp].time = 0; //set new page time flag to 0 since it was just "used"
                totalFaults++;
            } 
        }
        else if(selection == 3) //Second Chance
        {
            bool foundInCache = false;
            for(i = 0; i < C_SIZE; i++)
            {
                if(cache[i].pageno == page_num) //page found in cache
                {
                    cache[i].flag = 1; //set flag to 1 for page's second chance since it was looked up
                    foundInCache = true;
                    break;
                }
            }
            if(foundInCache == false)
            {
                totalFaults++;
		printf("Page fault at page %d \n", page_num);
                while(cache[replace].flag != 0) //look for first page that does not have bit set to 1
		{
			if(cache[replace].pageno == -1) //if page has not been added to table, add it
			{
				cache[replace].pageno = page_num;
				break;
			}
			if(cache[replace].flag == 1) //switch page with flag set to 1 to 0
			{
				cache[replace].flag = 0;
			}
			replace = (replace + 1) % C_SIZE; //increment replace cursor and make sure it does not go out of bounds
		}
		cache[replace].pageno = page_num; //when a page is found with flag set to 0, replace it with new page
		replace = (replace + 1) % C_SIZE; //also increment replace
            }
        }
        else
        {
            printf("Enter correct selection number for algorithm. \n");
            return 0;
        }
    }
    printf("%d Total Memory Requests \n", numRequests);
    printf("%d Total Page Faults \n", totalFaults);
    double faults = (double)totalFaults;
    double requests = (double)numRequests;
    double subtraction = requests - faults;
    printf("Miss Rate = %f \n", faults / requests);
    printf("Hit Rate = %f \n", subtraction / requests);
    return 0;
}
