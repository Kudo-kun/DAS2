#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define read(n) scanf("%d", &n)
#define print(n) printf("%d ",n)
#define endl printf("\n")

/****************************************************************************************************************************************************/
int val = 0, t;
/**
 * the following problem is done using binary trees.
 */
typedef struct nodetype
{
	int data;
	struct nodetype *right, *left;
}Node;

/**
 * the following function creates a node and appends it
 */
void appendLeaf(int x, Node** pos)
{
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp -> data = x; 
	tmp -> right = NULL; tmp -> left = NULL;
	*pos = tmp;
}

/**
 * initially x is appended into the root, i.e, starting dimension;
 * and at every state we have two other states to move into, i.e, 2*x or 10*x + 1;
 * val indicates if the required dimension has been reached or not;
 */
void setTree(int x, int y, int cnt, Node** pos)
{
	appendLeaf(x, pos);															//current dimension as root, and keep appending new nodes;
	if(cnt >= 0 && ((*pos) -> data) == y)										//when cnt >= 0 and state equals the required state;
		{ val = 1; return; }													//val = 1, function terminates and returns;
	if(!val && (2*x) <= y)														//till we exceed the required dimension, keep growing the left subtree;
		setTree(2*x, y, cnt -1, &((*pos) -> left));								//cnt is decreased with every new 'stage';
	if(!val && (10*x + 1) <= y)													//till we exceed the required dimension keep growing the right sub tree;
		setTree(10*x + 1, y, cnt - 1, &((*pos) -> right));						//cnt is decreased with every new 'stage';									
}

/**
 * Function to free the memory of a tree;
 * using post order traversal;
 */
void freeTree(Node **pos)
{
	if(*pos == NULL)
		return;
	else
	{
		freeTree(&(*pos) -> left);
		freeTree(&(*pos) -> right);
		free(*pos);
	}
}

/***************************************************************************************************************************************************/

int main()
{
	scanf("%d", &t);															//scan number of test cases;
	while(t--)
	{
		Node* root = NULL;														//root node;
		int x, y, cnt;
		scanf("%d%d%d", &x, &y, &cnt);
		setTree(x, y, cnt, &root);												//make the tree;
		(val == 1) ? printf("YES!") : printf("NO!"); endl;						//output decision;;
		freeTree(&root);														//Don't forget to free the tree;
	}
	return 0;
}