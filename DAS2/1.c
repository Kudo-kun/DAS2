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
int n, m;
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
	int selected[n], ans = 0;
	memset(selected, 0, n*sizeof(int));
	structSort(nodes);

	for(int i = 0; i < m; i++)
	{
		if(!selected[nodes[i].v1] || !selected[nodes[i].v2])
		{
			ans += nodes[i].cost;
			selected[nodes[i].v1] = 1;
			selected[nodes[i].v2] = 1;
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
	int selected[n]; memset(selected, 0, n*sizeof(int));
	
	for(int i = 0; i < m; i++)
		scanf("%d%d%d", &nodes[i].v1, &nodes[i].v2, &nodes[i].cost);

	print(findMinCost(nodes)); endl;
	return 0;
}