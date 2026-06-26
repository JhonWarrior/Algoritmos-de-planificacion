#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define COL 6 

//65 - A
//Jhonathan Lorenzo Rivas Guerrero - 11499
//Yael Jimena Chale Pech - 11245


void FCFS(int*,int); //Chale
void SJF(int*,int); //Jhon
void CM(int*,int); //Jhon
void RR(int*, int); //Chale
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
			FCFS(data,numProc);
			break;
		case 2:
			SJF(data,numProc);
			break;
		case 3:
			RR(data, numProc);
			break;
		case 4:
			CM(data,numProc);
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
		data[i*COL] = getData(1,3); //Col 0 - Prioridad
		printf("Uso CPU (1 a 10): ");
		data[i*COL+1] = getData(1,10); //Col 1 - CPU
		printf("Llegada (0 a 10): ");
		data[i*COL+2] = getData(0,10); //Col 2 - Llegada
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

void FCFS(int* data,int n){
	int aux[n*COL];
	int indices[n];
	int sumT = 0;

	for(int i = 0; i < n; i++){
		indices[i] = i;
		for(int j = 0; j < COL; j++)
		       aux[i*COL + j] = data[i*COL + j];	
	}


	for(int i = 0; i < n; i++)
	{
		for(int j = i+1; j < n; j++)
		{
			int aux1 = 0, aux2 = 0;
			if(aux[i*COL + 2] > aux[j*COL + 2])
			{
				aux1 = aux[i*COL + 2];
				aux[i*COL + 2] = aux[j*COL + 2];
				aux[j*COL + 2] = aux1;

				aux2 = indices[i];
				indices[i] = indices[j];
				indices[j] = aux2;
			}
		}
	}

	for(int i = 0; i < n; i++)
	{
		if(sumT < data[indices[i]*COL + 2])
			sumT = data[indices[i]*COL+2];

		sumT += data[indices[i]*COL+1];

		data[indices[i]*COL + 3] = sumT;
		
		data[indices[i]*COL + 4] = data[indices[i]*COL+3] - data[indices[i]*COL+2];
		data[indices[i]*COL + 5] = data[indices[i]*COL+4] - data[indices[i]*COL+1];	
	}

}
void SJF(int* data,int n){
	int completado[n];
	int terminados = 0, tiempo = 0;

	for(int i=0;i<n;i++) completado[i]=0;

	while(terminados < n){
		int min = -1;
		for(int i = 0;i<n;i++){
			if(!completado[i]&&(data[i*COL+2]<=tiempo)){//Si no ha terminado y el tiempo de llegada es menor o igual al tiempo del proceso
				if(min==-1||(data[i*COL+1]<data[min*COL+1])) min = i;//Si hay un CPU mas bajo actualizar, o si no hay ninguno asignar ese como el mas bajo
			}
		}
		if(min==-1){
			tiempo++;//Tiempo ++ si la llegada es mayor al tiempo contado
		}
		else{
			tiempo += data[min*COL+1];
			data[min*COL+3] = tiempo; //Finalizacion
			data[min*COL+4] = tiempo - data[min*COL+2]; //Retorno
			data[min*COL+5] = data[min*COL+4] - data[min*COL+1]; //Espera
			completado[min] = 1;
			terminados++;
		}
	}
}
void CM(int* data, int n){
	int completado[n],restante[n];
	int terminados = 0, tiempo = 0;
	
	printf("Ingresa el valor del quantum (2 a 5): ");
	int quantum = getData(2,5);

	for(int i = 0;i<n;i++){ 
		completado[i]=0;
		restante[i]=data[i*COL+1];
	}

	while(terminados < n){
		for(int prior = 3;prior>0;prior--){//Recorre prioridad
			for(int i = 0;i<n;i++){
				if(!completado[i]&&(data[i*COL+2]<=tiempo)&&(data[i*COL]==prior)){
					if(restante[i]>quantum){
						restante[i] -= quantum;
						tiempo += quantum;
					}
					else{
						tiempo += restante[i];
						restante[i] = 0;

						data[i*COL+3] = tiempo; //Finalizacion
						data[i*COL+4] = tiempo - data[i*COL+2]; //Retorno
						data[i*COL+5] = data[i*COL+4] - data[i*COL+1]; //Espera
						completado[i] = 1;
						terminados++;
					}
				}
			}
		}
	}
}

void RR(int* data, int n) {
	//Algoritmo de Round Robin

	int aux[n * COL];
	int cpu[n];
	int indices[n];
	int sumtot = 0;
	int sumT = 0, orden;

	printf("Ingresa el valor del quantum (2 a 5): ");
	int quantum = getData(2, 5);

	for (int i = 0; i < n; i++) {
		indices[i] = i;
		cpu[i] = data[i * COL + 1];
		sumtot += data[i * COL + 1];
		for (int j = 0; j < COL; j++)
			aux[i * COL + j] = data[i * COL + j];
	}

	for (int i = 0; i < n; i++)
	{
		int aux1, aux2;
		for (int j = i + 1; j < n; j++)
		{
			if (aux[i * COL + 2] > aux[j * COL + 2])
			{
				aux1 = aux[i * COL + 2];
				aux[i * COL + 2] = aux[j * COL + 2];
				aux[j * COL + 2] = aux1;

				aux2 = indices[i];
				indices[i] = indices[j];
				indices[j] = aux2;
			}
		}
	}

	while (sumT < sumtot)
	{
		orden = indices[0];
		if (cpu[indices[0]] > quantum)
		{
			cpu[indices[0]] -= quantum;
			sumT += quantum;
		}
		else if (cpu[indices[0]] > 0)
		{
			sumT += cpu[indices[0]];
			cpu[indices[0]] = 0;
			data[indices[0] * COL + 3] = sumT;
			data[indices[0] * COL + 4] = data[indices[0] * COL + 3] - data[indices[0] * COL + 2];
			data[indices[0] * COL + 5] = data[indices[0] * COL + 4] - data[indices[0] * COL + 1];
		}

		for (int j = 0; j < n - 1; j++)
			indices[j] = indices[j + 1];
		indices[n - 1] = orden;

		int p = indices[n - 1];

		for (int j = 0; j < n; j++)
		{
			if (data[indices[j] * COL + 2] > sumT)
			{
				for (int k = n - 1; k > j; k--)
					indices[k] = indices[k - 1];

				indices[j] = p;
				break;
			}
		}
	}
}
