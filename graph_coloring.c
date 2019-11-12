#include "graph.h"

void generate_two_different_numbers(int *vertexes_for_test_num, int n, int **A)
{
    while(1)
    {
        randombytes(&vertexes_for_test_num[0], sizeof(vertexes_for_test_num[0]));
        vertexes_for_test_num[0] = fabs(vertexes_for_test_num[0] % n);
        randombytes(&vertexes_for_test_num[1], sizeof(vertexes_for_test_num[1]));
        vertexes_for_test_num[1] = fabs(vertexes_for_test_num[1] % n);
        if(vertexes_for_test_num[0] != vertexes_for_test_num[1] &&
           is_adjacent(A[vertexes_for_test_num[0]][vertexes_for_test_num[1]]))
            break;
    }
}

int* load_colored(int *num_of_colors, int n, char *filename)
{
    int i, *vertexes;
    vertexes = malloc(n * sizeof(int));
    FILE *fout = file_open(filename, "r");
    *num_of_colors = 0;
    for(i = 0; i < n; i++){
        fscanf(fout, "%d ", &vertexes[i]);
        *num_of_colors = MAX(vertexes[i], *num_of_colors);
    }
    fclose(fout);
    return vertexes;
}


void load_graph_size(int *n, char *filename)
{
    FILE *fout = file_open(filename, "r");
    int m;
    fscanf(fout, "%d %d", n, &m);
    fclose(fout);
}


void relabeling(int n, int num_of_colors, int *vertexes)
{
    int i = 0, flag, j, tmp, colors[num_of_colors];
    printf("%d g", num_of_colors);
    /*for(; i < num_of_colors; i++)
    {
        flag = 1;
        randombytes(&tmp, sizeof(tmp));
        tmp = fabs(tmp % num_of_colors) + 1;
        while(flag)
        {
            flag = 0;
            for(j = 0; j < i; j++)
                if(colors[j] == tmp)
                {
                    flag = 1;
                    break;
                }
            if(flag)
            {
                tmp = (tmp + 1) % num_of_colors;
                if(tmp == 0)
                    tmp = num_of_colors;
            }
        }
        colors[i] = tmp;
    }*/
    /*for(i = 0; i < n; i++)
    {
        vertexes[i] = colors[vertexes[i] - 1];
    }*/
}

void save_colored(int *colored, int n, char *filename)
{
    int i;
    FILE *fout = file_open(filename, "w");
    for(i = 0; i < n; i++)
        fprintf(fout, "%d ", colored[i]);
    fclose(fout);
}

int **load_graph(int *m, int *n, char *filename)
{
    FILE *fout = file_open(filename, "r");
	int **A;
    int i = 0, vertex1, vertex2;
    fscanf(fout, "%d %d", n, m);
    if(*n > 1001 || *m > 1000)
    {
        fprintf(stderr, "n must be < 1001 and m must be <= 1000\n");
        exit(-1);
    }

    A = malloc(*n * sizeof(int*));
    for(; i < *n;i++)
        A[i] = calloc(*n, sizeof(int));
    for(i = 0; i < *m; i++)
    {
        fscanf(fout, "%d %d", &vertex1, &vertex2);
        A[vertex1][vertex2] = 1;
		A[vertex2][vertex1] = 1;
    }
    fclose(fout);
    return A;
}

inline int is_colored(int num)
{
	if(num != 0)
		return 1;
	return 0;	
}

inline int is_adjacent(int num)
{
    if(num != 0)
        return 1;
    return 0;
}

int can_be_colored(int **A,  int *colored, int n, int num, int color)
{
    int i;
    for(i = 0; i < n; i++)
        if(colored[i] == color && is_adjacent(A[num][i]))
            return 0;
    return 1;
}