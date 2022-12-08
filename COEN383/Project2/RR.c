#include <stdio.h>
#include <stdlib.h>
#include "stat.h"
#include "utility.h"

process_stat *createProcessStat(process* proc);

average_stats roundRobinP(linked_list * processes, int time_slice) {
	int t = 0;

	//Creation of  Process Queue
	queue *processQueue = (queue *)createQueue();
	node *procPtr = processes->head;
	if(processes->head == NULL) {
		fprintf(stderr,"No Process to schedule\n");
	}
	//keep checking while time quanta is less than 100 or the process queue is empty...
	process_stat * scheduledProcess = NULL;

	linked_list *ll = createLinkedList();
	printf("\nRound Robin Algorithm:\n");
	node *cur_node = NULL;
	int cur_run = 0;
	while(t<100 || processQueue->size > 0) {
		//check for incoming new process and do enqueue.
		if(procPtr != NULL && t<100) {
			process *newProcess = (process *)(procPtr->data);
			while(procPtr!=NULL && newProcess->arrivalTime <= t) {
				enqueue(processQueue,createProcessStat(newProcess));
				procPtr = procPtr->next;
				if(procPtr!=NULL)
					newProcess = (process *)(procPtr->data);
			}
		}

		//check process queue and schedule it if there is no scheduled process now..
		if(cur_node == NULL) {
			cur_run = 0;
			cur_node = processQueue->head;
		} else if(cur_run == time_slice) {
			cur_run = 0;
			cur_node = cur_node->next;
			if(cur_node == NULL) {
				cur_node = processQueue->head;
			}
		}

		if(cur_node != NULL) {
			scheduledProcess = (process_stat *) cur_node->data;
			process *proc = scheduledProcess->proc;

			if(t>=100) {
				if(scheduledProcess->startTime == -1) {
					//Do not start any new process, remove it from processQueue
					free(scheduledProcess);
					//dequeue(scheduledProcess);
					node *next = cur_node->next;
					removeNode(processQueue,cur_node->data);
					cur_node = next;
					cur_run = 0;
					continue;
				}
			}
			//add the currently running process to the time chart
			printf("%c",proc->pid);
			cur_run++;
			//update the current processes stat
			if(scheduledProcess->startTime == -1) {
				scheduledProcess->startTime = t;
			}
			scheduledProcess->runTime++;

			if(scheduledProcess->runTime >= proc->runTime) {
				scheduledProcess->endTime = t;
				addNode(ll,scheduledProcess);
				node * next = cur_node -> next;
				removeNode(processQueue, cur_node->data);
				cur_node = next;
				cur_run = 0;
			}
		} else {
			printf("_");
		}
		//keep increasing the time
		t++;
	}

	return printPolicyStat(ll);
	
}
