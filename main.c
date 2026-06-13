#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define COL 6 

//65 - A

void FCFS(); //Chale
void SJF(); //Jhon
void RR(); //Chale
void CM(); //Jhon
int getData(int,int);
int menu();
void init(int*,int);
void printTabla(int*,int);

int main(){
	int numProc;
	int r,opcion;

	printf("\n----------Algoritmos de planificacion----------\n\n");
	printf("Ingrese el numero de procesos que desee (max 15): ");
	numProc = getData(1,15);

	int* data = (int*)malloc(COL*numProc*sizeof(int)); 

	init(data,numProc);
	while(1){
		opcion = menu();

		switch (opcion){
		case 1:
			FCFS();
			break;
		case 2:
			SJF();
			break;
		case 3:
			RR();
			break;
		case 4:
			CM();
			break;
		case 5:
			free(data);
			data = NULL;
			return 0;
		}
		printTabla(data,numProc);
	}
}


int getData(int min,int max){
	int r,n;
	while(r=scanf("%d",&n) == 0||n<min||n>max){
		printf("Error al ingresar dato. Ingrese nuevamente: ");
		while(getchar()!='\n');
	}
	return n;
}

void init(int* data, int n){
	for(int i=0;i<n;i++){
		printf("\nProceso %c:\n",65+i);
		printf("Prioridad (1 a 3): ");
		data[i*COL] = getData(1,3); //Col 0
		printf("Uso CPU (1 a 10): ");
		data[i*COL+1] = getData(1,10); //Col 1
		printf("Llegada (0 a 10): ");
		data[i*COL+2] = getData(0,10); //Col 2
	}
}

void printTabla(int* data, int n){
	printf("\n%s%12s%12s%12s%12s%12s%12s\n","ID","Prioridad","Uso CPU","T. Llegada","T. Final","T. Retorno","T. Espera");
	for(int i = 0;i < n;i++){
		printf("%2c",65+i);
		for(int j = 0;j < COL;j++){
			printf("%12d",data[COL*i+j]);
		}
		printf("\n");
	}
	printf("\n");
}


int menu(){
	int opcion;
	printf("\nSelecciona el algoritmo de planificacion: \n"
	       "--------------------------\n"
	       "1. FCFS\n"
	       "2. SJF\n"
	       "3. Round Robin\n"
	       "4. Colas multinivel\n"
	       "5. Salir\n"
	       "--------------------------\n"
	       "Opcion: ");
	opcion = getData(1,5);
	return opcion;
}

void FCFS(){//TODO}
void SJF(){//TODO}
void RR(){//TODO}
void CM(){//TODO}
