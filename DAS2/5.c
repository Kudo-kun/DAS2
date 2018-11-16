#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define read(n) scanf("%d", &n)
#define print(n) printf("%d ",n)
#define endl printf("\n")
#define N 32
#define getBit(x, i) (((x & (1 << i))) ? 1 : 0)

/****************************************************************************************************************************************************/
int max_XOR = 0;
typedef struct nodetype
{
	int data;
	struct nodetype *left, *right;
}Node;

/**
 * a basic appending function that appends leafs to the tree;
 * index keeps track of the bit to be appended and must be greater than or equal to zero;
 * after appending a leaf, append the next bit as well at appropriate place;
 * all ones to the right and zeros to the left;
 */
void appendLeaf(Node** pos, int x, int index)
{
	if(*pos == NULL && index >= 0)
	{
		Node* tmp = (Node*)malloc(sizeof(Node));											//creates a node;
		tmp -> data = getBit(x, index); tmp -> right = NULL; tmp -> left = NULL;			//sets the node;
		*pos = tmp; --index;																//appends it and decreases index to get next bit;
	}
	if(index >= 0)																			//if the number can still be parsed;
	{
		int p = getBit(x, index);
		if(p == 0 && ((*pos) -> left) == NULL)												//if bit is 0 and left is null;
			appendLeaf(&((*pos) -> left), x, index);										//append it to the left;										
		else if(p == 0 && ((*pos) -> left) != NULL)											//if bit is 0, and left is blocked;										
			appendLeaf(&((*pos) -> left), x, --index);										//decrease index to get next bit, and move left without doing anything;
		else if(p == 1 && ((*pos) -> right) == NULL)										//if bit is 1, and right is null;
			appendLeaf(&((*pos) -> right), x, index);										//append it to the right;
		else if(p == 1 && ((*pos) -> right) != NULL)										//if bit is 1 and right id blocked;
			appendLeaf(&((*pos) -> right), x, --index);										//decrease index to get next bit, and move right without doing anything;
	}
	return;
}

/**
 * We try to parse the tree in a greedy approach;
 * if the bit is 1, we try to move left to encounter a 0 in the tree to maximize xor
 * but if left is null, we forcefully traverse to the right;
 * if bit if 0, we 'try' to move right, to encounter a 1, to maximize xor;
 * if both the bit and element in the node differ, then we add 'place' value of that element to the sum(max_XOR);
 * if both bit and element in the tree match, we move left or right according to the bit and availability of that child's pointer;
 * everytime we decrease the index to compare successive bits with the tree;
 */ 
void FindMaxXOR(Node** pos, int x, int index)
{
	if(index >=0 && (*pos) -> data != getBit(x, index))										//check if current bit is different for bit in the node;
		max_XOR += (1 << index);															//increment xor value;	
	if(index > 0)																
	{
		int p = getBit(x, index-1);
		if(p == 1 && (*pos) -> left == NULL)												//else if next bit in the sequence is 1, 'try' to move left, in an attempt to find a 0, if not possible, move right again;
			FindMaxXOR(&((*pos) -> right), x, --index);						
		else if(p == 1 && (*pos) -> left != NULL)											//if possible, 		
			FindMaxXOR(&((*pos) -> left), x, --index);										//move left;
		else if(p == 0 && (*pos) -> right == NULL)											//else if next bit in the sequence is 0, 'try' to move right, in an attempt to find a 1, if not possible, move left again;
			FindMaxXOR(&((*pos) -> left), x, --index);
		else if(p == 0 && (*pos) -> right != NULL)											//if possible, 			
			FindMaxXOR(&((*pos) -> right), x, --index);										//move right;			
	}
	return;
}

/***************************************************************************************************************************************************/

int main()
{
	int n, x, val;
	Node* root = NULL;																		//root node;
	
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
	{
		scanf("%d", &x);																	//scanning all integers with which comparisions have to be made;
		appendLeaf(&root, x, N-1);															//we append this number to the tree, taking into account prior common vertices
	}
	
	scanf("%d", &n);																		//scan the numbers to be compared;
	for(int i = 0; i < n; i++)
	{
		scanf("%d", &x); max_XOR = 0;														//initial max_XOR to 0 always;
		FindMaxXOR(&root, x, N-1);															//find the path in the tree with maximum number of complementary bit(compared to the number);
		print(max_XOR); endl;																//print the max_XOR;
	}
	return 0;
}