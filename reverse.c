// Solucion laboratorio 1
// Integrantes:
// Israel Velez Gonzalez
// Juan Esteban Ortiz

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_LINE_LENGTH 100

int main(int argc, char *argv[]) {
    FILE *inputFile = NULL;
    FILE *outputFile = stdout;  // Por defecto es la salida estándar
    char **lines = NULL;
    int numLines = 0;
    char buffer[MAX_LINE_LENGTH];
    // printf("Hola, mundo1!\n"); 
    // Caso: Sin argumentos -> Leer de stdin y escribir en stdout
    if (argc == 1) {
        inputFile = stdin; 
    }
    // Caso: Un argumento -> Leer de archivo y escribir en stdout
    else if (argc == 2) {
        inputFile = fopen(argv[1], "r");
        if (inputFile == NULL) {
            fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
            exit(1);
        }
    }
    // Caso: Dos argumentos -> Leer de archivo de entrada y escribir en archivo de salida
    else if (argc == 3) {
        inputFile = fopen(argv[1], "r");
        if (inputFile == NULL) {
            fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
            exit(1);
        }

        // Verificar si el archivo de entrada y salida son el mismo
        if (strcmp(argv[1], argv[2]) == 0) {
            fprintf(stderr, "reverse: input and output file must differ\n");
            fclose(inputFile);
            exit(1);
        }

        outputFile = fopen(argv[2], "w");
        if (outputFile == NULL) {
            fprintf(stderr, "reverse: cannot open file '%s'\n", argv[2]);
            fclose(inputFile);
            exit(1);
        }

        // Verificar si los archivos son hard links
        struct stat inputStat, outputStat;
        if (stat(argv[1], &inputStat) == -1 || stat(argv[2], &outputStat) == -1) {
            perror("Error al obtener información de archivo");
            fclose(inputFile);
            fclose(outputFile);
            return 1;
        }

        if (inputStat.st_ino == outputStat.st_ino) {
            fprintf(stderr, "reverse: input and output file must differ\n");
            fclose(inputFile);
            fclose(outputFile);
            exit(1);
        }
    }
    // Caso: Más de dos argumentos
    else {
        fprintf(stderr, "usage: reverse <input> <output>\n"); 
        exit(1);
    }

    // Leer las líneas del archivo y almacenarlas en un arreglo dinámico
    while (fgets(buffer, MAX_LINE_LENGTH, inputFile) != NULL) {
        // printf("in while\n"); 
        lines = realloc(lines, (numLines + 1) * sizeof(char *));
        lines[numLines] = malloc(strlen(buffer) + 1);
        strcpy(lines[numLines], buffer);
        numLines++;
    }
    // printf("out while\n"); 

    if (inputFile != stdin) {
        fclose(inputFile);  // Cerrar el archivo de entrada si no es stdin
    }

    // Escribir las líneas en orden inverso
    for (int i = numLines - 1; i >= 0; i--) {
        // printf("Hola, mundo!\n"); 
        fprintf(outputFile, "%s", lines[i]);
    }

    if (outputFile != stdout) {
        fclose(outputFile);  // Cerrar el archivo de salida si no es stdout
    }

    // Liberar la memoria dinámica
    for (int i = 0; i < numLines; i++) {
        free(lines[i]);
    }
    free(lines);

    return 0;
}
