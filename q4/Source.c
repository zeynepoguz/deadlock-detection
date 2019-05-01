#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <string.h>
#include<stdlib.h>
#define N 100 // size can change

int charToInt1D(int *intArr,char *arr, int n) {

	int i, index=0;

	for (i = 0; i < n; i++) {
		if (*(arr + i) != ' ') {
			*(intArr+index) = *(arr + i) - '0'; // char to int
			index++;
		}
	}

	return index;

}

int main() {


	char request[N][N], allocation[N][N], available[N];

	int r[N][N], alloc[N][N], ava[N];

	int i = 0, n=0, a=0;
	char line[N];

	FILE *fp;
	fp = fopen("state.txt", "r");
	
	if (fp == NULL) {
		printf("Error while opening the file.\n");
		return -1;
	}

	// get matrices 
	 while (fgets(line, sizeof(line), fp)) {
		 
		 if (line[0]=='\n') {
				 i++;
				 continue;
		 }
		 
		 switch (i)
		 {
			 
		 case 0:
			 strcpy(request[n], line);
			 n++;
			 break;
		 case 1:
			 strcpy(allocation[a], line);
			 a++;
			 break;
		 case 2:
			 strcpy(available, line);
			 break;
		 }	

    }


	 int len, process, p,m=0, f=0, numSource = 0, total_resource[N] = { 0 }, processes[N] = { 0 }, index = 0, times;
	 

	numSource = charToInt1D(ava, available, strlen(available));

	printf("# of resources = %d \n", numSource);

	 process = n; //len(request);
	 printf("# of processes = %d\n", process);
	 
	 for (i = 0; i < process; i++)
		 processes[i] = 1; // set all processes 1

	 len = strlen(allocation[0]);

	
		 for (p = 0; p < process; p++) {

			 charToInt1D(alloc[p], allocation[p], len);


			 for (i = 0; i < numSource; i++) {
				 total_resource[p] += alloc[p][i]; //calculate total resource that a process is allocated
			 }


			 if (total_resource[p] == 0) { // if there is no allocated resource then there is no deadlock
				 printf("\nMARKED P%d \n", p + 1);
				 processes[p] = -1; // mark the process (set its value to -1)
				 printf("New Available = ");
				 for (index = 0; index < numSource; index++) {
					 ava[index] += alloc[p][index];
					 alloc[p][index] = 0;
					 printf("%d ", ava[index]);
				 }
				 printf("\n\n------------------------\n");
			 }
		 }


		 len = strlen(request[0]);

			 for (p = 0; p < process; p++) {
				 if (m == 1) {
					 p = 0;
				 }

				 charToInt1D(r[p], request[p], len);

				 int t = 0;

				 for (index = 0; index < numSource; index++)
				 {
					 if (processes[p] == -1) //if process is already  marked 
					 {
						 m = 0; // continue loop flag
						 break; // exit no need to look at if its request <= W
					 }
					 if ( r[p][index] <= ava[index]) { // request <= W
						 t++;
					 }
					 else
					 {
						 m = 0; // if request > W continue loop
					 }
				 }

				 if (t == numSource) { // if process's request <= W
					 if (processes[p] != -1) {
						 printf("\nMARKED P%d \n", p + 1);
						 processes[p] = -1; // mark the process
						 printf("New Available = ");
						 for (index = 0; index < numSource; index++) {
							 ava[index] += alloc[p][index]; // W = W + Allocated(P)
							 alloc[p][index] = 0;
							 printf("%d ", ava[index]);
						 }
						 int t = 0;

						 for (i = 0; i < process; i++) // test how many process is marked
						 {
							 if (processes[i] == -1) // if it is marked 
								 t++;

						 }
						 if (t == process) { // if all processes are marked
							 f = t;
							 break; // end the loop
						 }

						 printf("\n\n------------------------\n");
						 m = 1; // flag - available vector has changed, go to first process and look again
					 }
					
				 }

			 }

			 

			 if (f == process) { // if all processes have marked
				 printf("\n\nRESULT: No Deadlock!\n");
				
			 }
			 else // if not all processes haven't marked 
			 {
				 printf("\n\nRESULT: Deadlock Detected");
				 printf("\nDeadlocked processes = ");

				 for (i = 0; i < process; i++)
				 {
					 if (processes[i] != -1) // unmarked process
						 printf("P%d  ", i + 1);

				 }

				
			 }

		 
	 

	fclose(fp);


	system("pause");



	return 0;
}