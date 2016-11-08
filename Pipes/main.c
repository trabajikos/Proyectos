#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char const *argv[]) {
	int fd[2]; // Pipe
	char buffer[15];
	pid_t pid;
	int retorno;

	retorno = pipe(fd);

	if (retorno == -1) {
		fprintf(stderr, "Error. No se ha podido crear el pipe\n");
	} else {
		pid = fork();
		switch(pid) {
			case -1:
				fprintf(stderr, "Error. No se ha podido crear el fork\n");
				exit(-1);
			case 0: // Proceso del hijo
				fprintf(stdout, "Hijo\n");
				char mensaje[] = "Yo soy tu hijo";
				// Siempre se escribe en la posición 1
				write(fd[1], mensaje, (strlen(mensaje) + 1) * sizeof(char));
				break;
			default: // Proceso del padre
				fprintf(stdout, "Padre\n");
				sleep(1);
				// Siempre se lee en la posición 0
				read(fd[0], &buffer, sizeof(buffer));
				fprintf(stdout, "%s\n", buffer);
				wait(NULL);
				break;
		}
	}
	return 0;
}