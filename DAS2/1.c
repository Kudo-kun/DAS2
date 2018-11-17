#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define read(n) scanf("%d", &n)
#define print(n) printf("%d ",n)
#define endl printf("\n")

/****************************************************************************************************************************************************/
/**
 * implements Kruskal's Algorithm;
 * a struct to hold both vertices and cost;
 */
int n, m, cycle = 0;
typedef struct
{
	int v1, v2, cost;
}Node;

/**an ordinary swap function*/
void swap(Node* a, Node* b)
{
	Node c = *a;
	*a = *b;
	*b = c;
	return;
}

/**
 * a sort function that sorts the given structs(which have vertices and cost),
 * according to the costs of the edges;
 * implements selection sort;
 */
void structSort(Node nodes[])
{
	for(int i = 0; i < m; i++)
		for(int j = i+1; j < m; j++)
			if(nodes[i].cost >= nodes[j].cost)
				swap(&nodes[i], &nodes[j]);
	return;
}

/**
 * An ordinary DFS function which will check if 'any' path from x will lead us to the required vertice somehow;
 * if x and req are disconnected, then we'll never be able to reach req from x;
 */
void DFS(int x, int req, int visited[], int mat[][n])
{
	if(!visited[x])																			//a visited array to keep track of all visited vertices;
	{
		if(x == req)																		//if we reach required vertice;
			{cycle = 1; return;}															//make cycle = 1, i.e, a cycle has been found;
		else
		{
			for(int j = 0; j < n; j++)														//else search the whole row for DFS points;
			{
				if(mat[x][j] == 1)															//if a DFS point is found
				{
					visited[x] = 1;															//mark the row as visited;
					DFS(j, req, visited, mat);												//and DFS at that point again;
				}
			}
		}
	}
}


/**
 * following function finds minimum cost of travel;
 * has an array which keeps track of the selected vertices;
 * First, sort all structs(according to cost, in increasing order);
 * chose the edge with minimum cost, check if forms a cycle with previous edges;
 * if no, add its cost to the min_cost and mark the the two vertices as selected;
 * else, don't else select them;
 * repeat;
 */
int findMinCost(Node nodes[])
{
	int mat[n][n], ans = 0, visited[n]; 													//make an adjacency matrix to keep track of vertices and visited array to keep track of visited vertices;
	memset(mat, 0, n*n*sizeof(int));														//initialize them to 0;
	structSort(nodes);																		//sort all the structs to get according to increasing cost;

	for(int i = 0; i < m; i++)
	{
		memset(visited, 0, n*sizeof(int)); cycle = 0;										//always initilize cycle to 0, and visited[n] to 0 before DFSing;
		DFS(nodes[i].v1, nodes[i].v2, visited, mat);										//DFS taking first vertex as x and sewcond vertex(which is to be reached) as req;
		if(!cycle)																			//if no cycle has been formed;
		{
			ans += nodes[i].cost;															//add the cost to the ans;
			mat[nodes[i].v1][nodes[i].v2] = 1;												//and mark those two vertices in the adjacency matrix;
			mat[nodes[i].v2][nodes[i].v1] = 1;												//remember it is undirected;
		}
	}
	return ans;
}

/**************************************************************************************************************************************************/

int main()
{
	/**
	 * scan both numbers;
	 * construct an array of structs which will hold both vertices and cost;
	 * selected array to keep track of selected vertices;
	 * invoke finMinCost to find min cost path
	 */
	scanf("%d%d", &n, &m);
	Node nodes[m];
		
	for(int i = 0; i < m; i++)
		scanf("%d%d%d", &nodes[i].v1, &nodes[i].v2, &nodes[i].cost);

	print(findMinCost(nodes)); endl;
	return 0;
}
