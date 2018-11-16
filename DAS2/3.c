#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define read(n) scanf("%d", &n)
#define print(n) printf("%d ",n)
#define endl printf("\n")

/****************************************************************************************************************************************************/
/**
 * implements the concept of articulation points or cut vertices
 */
int n, m, val = -1;

/** this function checks th enumber of zeros in an array*/
int checkZeroes(int arr[])
{
	for(int i = 0; i < n; i++)
		if(arr[i] == 0)
			return 1;

	return 0;
}

/**
 * a DFS function which will a forbidden vertex;
 * and also keep a visited array, to keep a check of all vertices that have been visited;
 * and an adjacency matrix, to keep track edges between vertices;
 */
void DFS(int r, int x, int visited[], int mat[][n])
{
	if(x != r && !visited[x])												// make sure that we don't visit the forbidden vertex or a prior visited vertex;
	{
		for(int j = 0; j < n; j++)
		{
			if(mat[x][j] == 1)												//if a DFS point is found;
			{
				visited[x] = 1;												//mark that row as visited and DFS again at that point;
				DFS(r, j, visited, mat);
			}
		}
		visited[x] = 1;														//even if no DFS points were present, make sure to mark it as visited after traversing it;
	}
	return;
}

/**
 * in this function, we assume each vertex is a cut vertex;
 * and mark it as 'forbidden' (visited = -1), i.e, apparently removing it;
 * if we classify first vertex itself as forbidden;
 * we traverse the whole graph starting from the second vertex;
 * else we traverse the graph from first vertex itself;
 * if after traversal a certain node(s) weren't visited at all, we can say the selected vertex was a cut vertex;
 */
void articulationPoints(int mat[][n])
{
	for(int i = 0; i < n; i++)
	{
		int visited[n]; memset(visited, 0, n*sizeof(int));
		visited[i] = -1;
		(i == 0) ? DFS(i, 1, visited, mat) : DFS(i, 0, visited, mat);
		
		if(checkZeroes(visited))											//to check is a node(s) was visited or not;
			{print(i); val = 1;}											//we check if visited index of that vertex is true or false
	}																		//if after traversal, if atleast one vertex as visitedindex as false, the initially chosen vertex is a cut vertex;
	return;
}

/****************************************************************************************************************************************************/

int main()
{
	scanf("%d%d", &n, &m);
	int mat[n][n]; memset(mat, 0, n*n*sizeof(int));							//set all elements of matrix to 0;
	for(int i = 0; i < m; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		mat[x][y] = 1; mat[y][x] = 1;										//mark all DFS points(edges);
	}

	articulationPoints(mat); endl;
	print(val); endl;														//print the following if no articulation points are present;
	return 0;
}