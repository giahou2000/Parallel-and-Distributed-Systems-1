#include <stdio.h>
#include <stdlib.h>
#include "../include/read_matrix.h"

/**
 * read_graph_matrix - Read an undirected, unweighted graph from a file
 * 
 * This function reads an adjacency matrix from a file where each element is 0 or 1.
 * For an undirected graph, the matrix should be symmetric (matrix[i][j] == matrix[j][i]).
 * 
 * File format:
 * - First line: number of vertices (n)
 * - Next n lines: n space-separated integers per line (adjacency matrix)
 */
int** read_matrix(const char* filename, int* rows, int* cols)
{
    FILE* file;
    int n, i, j; // number of vertices, loop counters
    int** matrix;

    if (filename == NULL || rows == NULL || cols == NULL) {
        fprintf(stderr, "Error: Invalid arguments to read_matrix\n");
        return NULL;
    }

    /* Open the file for reading */
    file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file '%s'\n", filename);
        return NULL;
    }

    /* Read the number of vertices */
    if (fscanf(file, "%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Error: Invalid matrix size\n");
        fclose(file);
        return NULL;
    }

    *rows = n;
    *cols = n;

    /* Allocate memory for the matrix */
    matrix = (int**)malloc(n * sizeof(int*));
    if (matrix == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for rows\n");
        fclose(file);
        return NULL;
    }

    for (i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
        if (matrix[i] == NULL) {
            fprintf(stderr, "Error: Memory allocation failed for column %d\n", i);
            /* Free previously allocated memory */
            for (j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            fclose(file);
            return NULL;
        }
    }

    /* Read the adjacency matrix */
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (fscanf(file, "%d", &matrix[i][j]) != 1) {
                fprintf(stderr, "Error: Failed to read matrix element at [%d][%d]\n", i, j);
                /* Free allocated memory */
                for (int k = 0; k < n; k++) {
                    free(matrix[k]);
                }
                free(matrix);
                fclose(file);
                return NULL;
            }

            /* Validate that values are 0 or 1 */
            if (matrix[i][j] != 0 && matrix[i][j] != 1) {
                fprintf(stderr, "Error: Invalid value %d at [%d][%d]. Expected 0 or 1\n", 
                        matrix[i][j], i, j);
                for (int k = 0; k < n; k++) {
                    free(matrix[k]);
                }
                free(matrix);
                fclose(file);
                return NULL;
            }
        }
    }

    fclose(file);
    return matrix;
}

/**
 * free_matrix - Free memory allocated for a matrix
 */
void free_matrix(int** matrix, int rows)
{
    if (matrix == NULL)
        return;

    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
