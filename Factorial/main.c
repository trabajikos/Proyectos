#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
	int fd[2];
	int retorno;
	unsigned long long int resultado = 1;
	unsigned long long int resultado_hijo;
	int objetivo;
	int medio_obejtivo;
	pid_t pid;

	if (argc != 2) {
		fprintf(stderr, "Error. Debe introducir una variable\n");
		exit(-1);
	}
	objetivo = atoi(argv[1]);
	if (objetivo < 1 || objetivo > 20) {
		fprintf(stderr, "La variable debe estar comprendida entre el 1 y el 20\n");
		exit(-1);
	}
	
	retorno = pipe(fd);
	if (retorno == -1) {
		fprintf(stderr, "Error. No se ha podido crear el pipe\n");
		exit(-1);
	} 

	medio_obejtivo = objetivo / 2;
	pid = fork();
	switch(pid) {
		case -1:
				fprintf(stderr, "Error. No se ha podido crear el fork\n");
				exit(-1);
		case 0: // Proceso del hijo
			for (int i = objetivo; i > medio_obejtivo; i--) {
				resultado = resultado * i;
			}
			write(fd[1], &resultado, sizeof(unsigned long long int));
			break;
		default: // Proceso del padre
			for (int i = medio_obejtivo; i > 0; i--) {
				resultado = resultado * i;
			}
			read(fd[0], &resultado_hijo, sizeof(unsigned long long int));
			wait(NULL);
			resultado = resultado * resultado_hijo;
			fprintf(stdout, "El factorial de %d es: %llu\n", objetivo, resultado);
			break;
	}	
	return 0;
}