#include <stdlib.h>
#include <stdio.h>

#include <bool.h>

enum {
	ID,
	START,
	END,
	PRIORITY,
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
#define ANS_SIZE 4

int compare_by_id(const void *p1, const void *p2) {
	const int *proc1 = *(const int **)p1;
	const int *proc2 = *(const int **)p2;
	return proc1[ID] - proc2[ID];
}

int update_id(int **procs, int size, int pid) {
	for (int i = 0; i < size; ++i) {
		if(procs[i][ID] == pid) {
			i = 0;
			pid++;
		}
	}
		
	return pid;
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
	bool has_special_priority = false;

	if(is_fifo) {
		// as mentioned in the defines, if the scheduling strategy is FIFO,
		// we won't recieve the priority of a given process from the input
		while(!feof(input)) {
			int pid, start, end;

			scanf("%d %d %d", &pid, &start, &end);

			procs[procs_size] = (int *) malloc(sizeof(int) * PROC_INFO_FIFO_SIZE);

			int new_id = update_id(procs, procs_size, pid);

			procs[procs_size][ID] = new_id;
			procs[procs_size][START] = start;
			procs[procs_size][END] = end;

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
			procs[procs_size][END] = end;
			procs[procs_size][PRIORITY] = priority;

			if(priority == 0)
				has_special_priority = true;

			procs_size++;
		}
	}

	if(is_fifo) {
		printf("FIFO!\n");
		// qsort(procs, procs_size, sizeof(int *), compare_by_id);

		int loop = 0;
		for (int i = 0; i < procs_size; ++i) {
			printf("proc %d = %d %d %d %d\n", i, procs[i][ID], procs[i][START], procs[i][END], procs[i][PRIORITY]);
			free(procs[i]);
		}
	} else {
		for (int i = 0; i < procs_size; i++) {
			printf("proc %d = %d %d %d %d\n", i, procs[i][ID], procs[i][START], procs[i][END], procs[i][PRIORITY]);
			free(procs[i]);
		}
	}

	free(procs);

	return 0;
}