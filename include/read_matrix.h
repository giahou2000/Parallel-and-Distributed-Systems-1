#ifndef READ_MATRIX_H
#define READ_MATRIX_H

/**
 * read_graph_matrix - Read an undirected, unweighted graph from a file into a matrix
 * @filename: The path to the input file
 * @rows: Pointer to store the number of rows (vertices)
 * @cols: Pointer to store the number of columns (vertices)
 *
 * The input file should contain:
 * - First line: number of vertices (n)
 * - Following n lines: each line contains n space-separated integers (0 or 1)
 *   where 1 indicates an edge between vertices and 0 indicates no edge
 *
 * Returns: A pointer to a 2D array (adjacency matrix) on success, NULL on failure
 *          The caller is responsible for freeing the allocated memory
 */
int** read_graph_matrix(const char* filename, int* rows, int* cols);

/**
 * free_matrix - Free the memory allocated for a matrix
 * @matrix: The matrix to free
 * @rows: Number of rows in the matrix
 */
void free_matrix(int** matrix, int rows);

#endif
