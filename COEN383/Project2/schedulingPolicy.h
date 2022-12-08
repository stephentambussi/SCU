#ifndef _scheduling_policy_h
#define _scheduling_policy_h



//enum State {UNUSED, EMBRYO, SLEEPING, RUNNING, ZOMBIE};

struct process_stat_s {
	(Process *) proc;
	unsigned float waitingTime;
	unsigned float completion_time;
	unsigned float turnaroundTime;
	unsigned float responseTime;

	enum State state;
}
typedef struct process_stat_s ProcessStat;

struct stat_s {
	(linked_list *) processQueue;
	(linked_list *) time_chart;
	unsigned float avg_turnaround_time;
	unsigned float avg_waiting_time;
	unsigned float avg_response_time;
	unsigned float throughput;
	int total_quanta;
}
typedef struct stat_s SchedulingStat;
/*
SchedulingStat * firstComeFirstServeNP(linked_list * processes);
SchedulingStat * shortestJobFirstNP(linked_list * processes);
SchedulingStat * shortestRemainingTimeP(linked_list * processes);
SchedulingStat * roundRobinP(linked_list * processes,int time_slice);
SchedulingStat * highestPriorityFirstP(linked_list * processes);
SchedulingStat * highestPriorityFirstNP(linked_list * processes);
SchedulingStat * highest_priority_first_p_aging(linked_list * processes);
SchedulingStat * highest_priority_first_np_aging(linked_list * processes);
*/
#endif
