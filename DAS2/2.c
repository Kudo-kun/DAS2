#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define read(n) scanf("%d", &n)
#define print(n) printf("%d ",n)
#define endl printf("\n")

/****************************************************************************************************************************************************/
/**
 * implements travelling salesman problem;
 */
int m, n, minCost = 1e4, fin_ans[5];

/**ordinary swap function*/
void swap(int* a, int* b)
{
	int c = *a;
	*a = *b;
	*b = c;
}

/**
 * following function calculates cost of path;
 * Imp: path array must of the form, {0 1 2 3 4 0};
 * first checks if an edge exists between two vertices, which are given by the consecutive elements of the 'path' array;
 * if edge exist, we find its cost, keeping in mind it is bidirectional;
 * at the end, after the cost is found, we check if it is lesser than prior minCost,
 * and if yes, we update the minCost;
 */
void pathCost(int path[], int mat[][3])
{
	int cost = 0;
	for(int i = 0; i <= n; i++)
		for(int j = 0; j < m; j++)
			if((path[i] == mat[j][0] && path[i+1] == mat[j][1]) || (path[i] == mat[j][1] && path[i+1] == mat[j][0])) 
				cost += mat[j][2];
	
	if(cost <= minCost)
	{
		minCost = cost;
		for(int i = 0; i < n+1; i++)
			fin_ans[i] = path[i];
	}
}

/**
 * finds all possible paths by permuatations;
 * once a new permutation is formed, check for its cost
 */
void MinimunCostPath(int l, int r, int path[], int mat[][3])
{
	if(l == r)
		pathCost(path, mat);
	else
	{
		for(int i = l; i <= r; i++)
		{
			swap(&path[i], &path[l]);
			MinimunCostPath(l+1, r, path, mat);
			swap(&path[i], &path[l]);
		}
	}
}


/***************************************************************************************************************************************************/
/**
 * Basically, we assume if a hamiltoninan path exists;
 * we can traverse that path starting from any vertice;
 * therefore we chose to start from 0 itself and end at 0 again;
 */
int main()
{
	scanf("%d%d", &n, &m);
	int mat[m][3], path[n+1];										//size is n+1 coz, we need to add the starting node at the end again, i.e, {0, 1, 2, 3, 0}
	for(int i = 0; i < m; i++)
		scanf("%d%d%d", &mat[i][0], &mat[i][1], &mat[i][2]);		//keep a matrix which will keep a record pf the edges and their costs;

	path[n] = 0;													//always keep last element (n+1)th elemnt as 0;							
	for(int i = 0; i < n; i++)
		path[i] = i;												//and start with a sequence of {0, 1, 2, 3, 4, 0} (size is according to n);

	MinimunCostPath(1, n-1, path, mat); endl;						//find min_cost. (Note, it is n-1;)
	for(int i = 0; i < n+1; i++)
		printf("%c ", 65 + fin_ans[i]);								//print path with min cost;
	
	printf("\nCost: %d\n", minCost);								//print path cost;
	return 0;
}