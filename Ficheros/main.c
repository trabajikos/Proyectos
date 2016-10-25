#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[]) {
	int fdLeer, fdEscribir; // File Descriptor
	char buffer[15];

	// Abre los ficheros
	fdLeer = open("./leer.txt", O_RDONLY);
	fdEscribir = open("./escribir.txt", O_WRONLY);
	// Comprueba si se pueden abrir los ficheros
	if (fdLeer == -1 | fdEscribir == -1) {
		fprintf(stderr, "¡BOOM! El fichero no se puede abrir\n");
	} else {
		// Lee del fichero y lo guarda en el buffer
		read(fdLeer, buffer, 15 * sizeof(char));
		// Escribe al fichero el buffer
		write(fdEscribir, buffer, 15 * sizeof(char));
		// Cierra los ficheros
		close(fdLeer);
		close(fdEscribir);
	 }
	return 0;
}