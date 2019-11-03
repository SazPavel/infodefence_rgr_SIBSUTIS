#ifndef graph_h
#define graph_h

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "randombytes.h"
#include "infodef.h"
#include "ciphers.h"

#define MAX(a,b) (((a)>(b))?(a):(b))

void save_colored(int *colored, int n, char *filename);
int **load_graph(int *m, int *n, char *filename);
extern int is_colored(int num);
extern int is_adjacent(int num);
int can_be_colored(int **A,  int *colored, int n, int num, int color);
void relabeling(int n, int num_of_colors, int *vertexes);
void load_graph_size(int *n, char *filename);
int* load_colored(int *num_of_colors, int n, char *filename);
void generate_two_different_numbers(int *vertexes_for_test_num, int n, int **A);
#endif