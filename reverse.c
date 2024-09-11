// Solucion laboratorio 1
// Integrantes:
// Israel Velez Gonzalez
// Juan Esteban Ortiz

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <nombre_archivo>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error al abrir el archivo: %s\n", argv[1]);
        return 1;
    }

    char **lines = NULL;
    int numLines = 0;
    char buffer[MAX_LINE_LENGTH];

    // Leer las líneas del archivo y almacenarlas en un arreglo dinámico
    while (fgets(buffer, MAX_LINE_LENGTH, file) != NULL) {
        lines = realloc(lines, (numLines + 1) * sizeof(char *));
        lines[numLines] = malloc(strlen(buffer) + 1);
        strcpy(lines[numLines], buffer);
        numLines++;
    }

    fclose(file);

    // Imprimir las líneas en orden inverso
    for (int i = numLines - 1; i >= 0; i--) {
        printf("%s", lines[i]);
    }

    // Liberar la memoria dinámica
    for (int i = 0; i < numLines; i++) {
        free(lines[i]);
    }
    free(lines);

    return 0;
}
