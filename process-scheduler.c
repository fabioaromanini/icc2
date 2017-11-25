#include <stdlib.h>
#include <stdio.h>

#include <bool.h>

enum {
	ID,
	START,
	REMAINING,
	PRIORITY,
};

typedef struct list_node proc;

struct list_node {
	proc *next;
	bool executed;
	int id;
	int remaining_time;
	int priority;
};


// as we don't know how many processes we'll read,
// we'll use this define to guess the number of processes,
// based on the test cases
#define N_PROC 10

// if the scheduling strategy is FIFO, we won't
// use any priority to order them, therefore, the
// vector wich contains the info about a process
// we'll be smaller
#define PROC_INFO_FIFO_SIZE 3
#define PROC_INFO_SIZE 4
#define ANS_SIZE 2
#define FINISH_TIME 1

// used for FIFO strategy
int compare_by_start_then_id(const void *p1, const void *p2) {
	const int *proc1 = *(const int **)p1;
	const int *proc2 = *(const int **)p2;

	if(proc1[START] != proc2[START])
		return proc1[START] - proc2[START];
	
	return proc1[ID] - proc2[ID];
}

int compare_by_start_then_priority(const void *p1, const void *p2) {
	const int *proc1 = *(const int **)p1;
	const int *proc2 = *(const int **)p2;

	if(proc1[START] != proc1[START])
		return proc1[START] - proc2[START];
	
	return proc2[PRIORITY] - proc1[PRIORITY];
}

// prevents repeated IDs
int update_id(int **procs, int size, int pid) {
	for (int i = 0; i < size; ++i) {
		if(procs[i][ID] == pid) {
			i = 0;
			pid++;
		}
	}
		
	return pid;
}

bool ack_new_procs(proc **procs_list, int **procs, int procs_size, int loop) {
	bool ackd_new = false;

	for(int i = 0; i < procs_size; i++) {
		if(procs[i][START] == loop) {
			ackd_new = true;
			if((*procs_list) == NULL) {
				(*procs_list) = (proc *) malloc(sizeof(proc));
				(*procs_list)->next = NULL;
				(*procs_list)->executed = false;

				(*procs_list)->id = procs[i][ID];
				(*procs_list)->remaining_time = procs[i][REMAINING];
				(*procs_list)->priority = procs[i][PRIORITY];
			} else {
				proc *aux = (*procs_list);

				if(aux->priority < procs[i][PRIORITY]) {
					proc *new = (proc *) malloc(sizeof(proc));
					new->executed = false;

					new->id = procs[i][ID];
					new->remaining_time = procs[i][REMAINING];
					new->priority = procs[i][PRIORITY];
					
					new->next = aux;
					(*procs_list) = new;
					continue;
				}
				
				while(aux->next != NULL && aux->next->priority > procs[i][PRIORITY]) {
					aux = aux->next;
				}

				proc *new = (proc *) malloc(sizeof(proc));
				new->executed = false;

				new->id = procs[i][ID];
				new->remaining_time = procs[i][REMAINING];
				new->priority = procs[i][PRIORITY];
				new->next = aux->next;

				aux->next = new;
			}
		}
	}

	return ackd_new;
}

bool done(proc *procs) {
	while(procs != NULL) {
		if(procs->remaining_time > 0)
			return false;

		procs = procs->next;
	}

	return true;
}

void reset_list(proc *procs) {
	while(procs != NULL) {
		procs->executed = false;
		procs = procs->next;
	}
}

proc *next_process(proc *procs) {
	proc *aux = procs;
	
	while(aux != NULL) {
		if(aux->executed == false && aux->remaining_time > 0)
			return aux;
		aux = aux->next;
	}

	reset_list(procs);

	return procs;
}

int main(int argc, char const *argv[]) {
	FILE *input = stdin;
	char ordering;
	bool is_fifo = false;

	scanf("%c ", &ordering);

	if(ordering == 'f')
		is_fifo = true;
	else
		fseek(input, 0, SEEK_SET);
	
	int **procs = (int **) malloc(sizeof(int *) * N_PROC);
	int procs_size = 0;

	if(is_fifo) {
		// as mentioned in the defines, if the scheduling strategy is FIFO,
		// we won't recieve the priority of a given process from the input
		while(!feof(input)) {
			int pid, start, end;

			scanf("%d %d %d", &pid, &start, &end);

			procs[procs_size] = (int *) malloc(sizeof(int) * PROC_INFO_FIFO_SIZE);

			// check for repeated id's
			int new_id = update_id(procs, procs_size, pid);

			procs[procs_size][ID] = new_id;
			procs[procs_size][START] = start;
			procs[procs_size][REMAINING] = end;

			procs_size++;
		}
	} else {
		while(!feof(input)) {
			int pid, start, end, priority;

			scanf("%d %d %d %d ", &pid, &start, &end, &priority);

			procs[procs_size] = (int *) malloc(sizeof(int) * PROC_INFO_SIZE);

			int new_id = update_id(procs, procs_size, pid);

			procs[procs_size][ID] = new_id;
			procs[procs_size][START] = start;
			procs[procs_size][REMAINING] = end;
			procs[procs_size][PRIORITY] = priority;

			procs_size++;
		}
	}

	if(is_fifo) {
		// if we're using fifo strategy, there is no need to simulate a 
		// loop, so, we'll just execute the proccess according to the
		// order in which they were acknowledge

		qsort(procs, procs_size, sizeof(int *), compare_by_start_then_id);
		
		int loop = 0;
		for (int i = 0; i < procs_size; ++i) {
			printf("%d %d\n",procs[i][ID], loop + procs[i][REMAINING]);
			loop += procs[i][REMAINING];
			free(procs[i]);
		}
	} else {

		int loop = 1;
		proc *procs_list = NULL;

		int **answer = (int **) malloc(sizeof(int *) * procs_size);
		int ans_size = 0;
		
		do {
			if(ack_new_procs(&procs_list, procs, procs_size, loop)) {
				reset_list(procs_list);
			}

			proc *actual = next_process(procs_list);

			// printf("list:\n");
			// proc *aux  = procs_list;
			// while(aux != NULL) {
			// 	printf("%d ", aux->id);
			// 	aux = aux->next;
			// }
			// printf("Chosen id: %d\n", actual->id);

			actual->executed = true;
			actual->remaining_time -= 1;
			if(actual->remaining_time == 0) {
				answer[ans_size] = (int *) malloc(sizeof(int) * ANS_SIZE);
				answer[ans_size][ID] = actual->id;
				answer[ans_size][FINISH_TIME] = loop;
				
				ans_size++;
			}
			
			loop++;

		} while(!done(procs_list));

		while(procs_list != NULL) {
			proc *aux = procs_list->next;
			free(procs_list);
			procs_list = aux;
		}


		for(int i = 0; i < ans_size; i++) {
			printf("%d %d\n", answer[i][ID], answer[i][FINISH_TIME]);
			free(answer[i]);
		}

		free(answer);

		for (int i = 0; i < procs_size; i++)
			free(procs[i]);
	}

	free(procs);

	return 0;
}