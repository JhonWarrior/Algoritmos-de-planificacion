#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//65 - A

void FCFS();
void SJF();
void RoundRobin();
void ColasMultinivel();
int getData(int,int);

int main(){
	int numProc;
	int r;
	printf("----------Algoritmos de planificacion----------\n\n");
	printf("Ingrese el numero de procesos que desee (max 15): ");
	numProc = getData(1,15);

	int* data = (int*)malloc(3*numProc*sizeof(int)); 

	for(int i=0;i<numProc;i++){
		printf("\nProceso %c:\n",65+i);
		printf("Prioridad (1 a 3): ");
		data[i*3] = getData(1,3); 
		printf("Uso CPU (1 a 10): ");
		data[i*3+1] = getData(1,10); 
		printf("Llegada (0 a 10): ");
		data[i*3+2] = getData(0,10); 
	}

	printf("\n%-3s %-10s %-10s %-10s\n","ID","Prioridad","Uso CPU","Llegada");
	for(int i = 0;i < numProc;i++){
		printf("%-8c%-10d%-11d%d\n",65+i,data[i*3],data[i*3+1],data[i*3+2]);
	}
	free(data);
	data = NULL;
	return 0;
}

int getData(int min,int max){
	int r,n;
	while(r=scanf("%d",&n) == 0||n<min||n>max){
		printf("Error al ingresar dato. Ingrese nuevamente: ");
		while(getchar()!='\n');
	}
	return n;
}

