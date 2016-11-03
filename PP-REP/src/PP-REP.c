#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "LibparF.h"


int main(int argc, char *argv[]) {
	int pid1,pid2,pid3,pidF,fin1 = 0,fin2 = 0,fin3 = 0,estado;
	tnodo nodo [3];
	if(argc != 2)
	{
		printf("Tiene que introducir 1 argumento, no %d \n",argc);
		return 1;
	}
	if(atoi(argv[0]) != 2 || atoi(argv[0]) !=3)
	{
		printf("El argumento ha de valer 2 o 3, no %d \n",atoi(argv[0]));
		return 1;
	}

	if((pid1 = fork()) != 0)
	{
		if((pid2 = fork()) != 0)
		{

			if((pid3 = fork()) != 0)//PADRE
			{
				printf("Soy el padre y he lanzado 3 hijos, y estoy esperando a que terminen los hijos\n");
				do
				{
					pidF = wait(&estado);
					if(pidF == pid1)
					{
						printf("Ha acabado el hijo nº 1, que tenía un pid de %i \n",pid1);
						pid1 = 1;
					}
					else if(pidF == pid2)
					{
						printf("Ha acabado el hijo nº 2, que tenía un pid de %i \n",pid2);
						pid2 = 1;
					}
					if(pidF == pid3)
					{
						printf("Ha acabado el hijo nº 3, que tenía un pid de %i \n",pid3);
						pid3 = 1;
					}
				}while(!fin1 || !fin2 || !fin3);
			}
			else//HIJO3
			{
				printf("Soy el hijo 3 y mi pid es %d \n",getpid());


				printf("Soy el hijo 3 y lanzo 3 funciones concurrentes \n");

				parbegin(3,nodo);
				//TODO: lanzar


			}
		}
		else//HIJO2
		{
			printf("Soy el hijo 2, y tengo un pid de: %d \n",getpid());
			pidF = wait(&estado);
			printf("He recibido la senyal y continuo \n");
			kill(pid1,9);
			printf("Soy el hijo 2, he matado a mi hermano con pid %d y termino\n",pid1);
			exit(0);
		}
	}
	else//HIJO1
	{
		printf("Soy el hijo 1, con pid de: %d y me quedo en un bucle infinito \n",getpid());
		while(1);
	}

	return 0;
}

