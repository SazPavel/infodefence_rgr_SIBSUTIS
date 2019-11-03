#include "graph.h"

int main()
{
	int n, m, i, num1, num2, color = 1;
	int **A;
	int *colored;
	num1 = num2 = -1;
	A = load_graph(&m, &n, "tmp/graph");
   /* for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        	printf("%d ", A[i][j]);
        printf("\n");
    }*/
    colored = calloc(n, sizeof(int));
    for(num1 = 0; num1 < n; num1++)
    {
    	if(!is_colored(colored[num1]))
    	{
    		if(!can_be_colored(A, colored, n, num1, color))
    		{
    			color += 1;
                colored[num1] = color;
    		}
            num2 = num1;
            while(num2 < n)
            {
                if(!is_colored(colored[num2]) && can_be_colored(A, colored, n, num2, color))
                {
                    colored[num2] = color;
                }
                num2 += 1;
            }  
    	}
    }
    save_colored(colored, n, "tmp/graph2");
    /*for(i = 0; i < n; i++)
        printf("%d ", colored[i]);
    printf("\n");*/
    for(i = 0; i < n; i++)
        free(A[i]);
    free(A);
    free(colored);
    exit(0);
}