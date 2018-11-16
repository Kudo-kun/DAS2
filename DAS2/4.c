#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define read(n) scanf("%d", &n)
#define print(n) printf("%d ",n)
#define endl printf("\n")

/****************************************************************************************************************************************************/
/**
 * A brute force method of finding if two graphs are isomorphic;
 * Basically we try to find a one to one-one correspondence between the vertices;
 * therefore, if an edge occurs between two vertices is graph g1, then an edge must occur between their 'corresponding' vertices as well;
 */
int val = 0, n1, m1, n2, m2;

/**
 * An ordinary swap function
 */
void swap(int*a, int* b)
{
    int c = *a; 
    *a = *b; 
    *b = c;
}

/**
 * The following funtions finds if the given two numbers are present in order in the matrix;
 */
int check(int x, int y, int B[][2])
{
    for(int i = 0; i < m2; i++)                                                         //runs through all rows of 'edges' matrix;
        if(B[i][0] == x && B[i][1] == y)                                                //tries to find is a corresponding edge is present;
            return 1;
    
    return 0;
}

/**
 * the following function tries to check one-one correspondence between two graphs g1, g2;
 * g1: any random permutation (arr in this case);
 * g2: {0, 1, 2, 3, ..., n-1} (array indices in this case);
 */
int findEdges(int arr[], int A[][2], int B[][2])
{
    for(int i = 0; i < m1; i++)                                                         //for every edge between two vertices of g1;
        if(check(arr[A[i][0]], arr[A[i][1]], B) == 0)                                   //we try to find an edge between their corresponding vertices;
            return 0;                                                                   //if no such edge is found, isomorphism between g1 and g2 is not possible;
    
    return 1;
}

/**
 * find all permutationsof the given vertices, i.e, all possible arrangements of the graph;
 * if a suitable permutation is found, function terminates and returns;
 */
void checkIsomorphism(int l, int r, int arr[], int A[][2], int B[][2])
{
    if(l == r && !val && findEdges(arr, A, B))                                          //if a new permutation forms;
        { val = 1; return; }                                                            //check if it satisfies the iosmorphism or one to one relationship;
    else if(!val)
    {
        for(int i = l; i <= r; i++)
        {
            swap(&arr[i], &arr[l]);
            checkIsomorphism(l+1, r, arr, A, B);
            swap(&arr[i], &arr[l]);
        }
    }
}

/***************************************************************************************************************************************************/

int main()
{
	scanf("%d%d", &n1, &m1);
    int A[m1][2];
    for(int i = 0; i < m1; i++)
        scanf("%d%d", &A[i][0], &A[i][1]);                                               //scan the 'edges' matrix1;

    scanf("%d%d", &n2, &m2);
    int B[m2][2], arr[n2];                                      
    for(int i = 0; i < m2; i++)
        scanf("%d%d", &B[i][0], &B[i][1]);                                               //scan 'edges' matrix2; 
    for(int i = 0; i < n2; i++)
        arr[i] = i;                                                                      //since vertices are named from 0, n-1, consider them as an array, {0,1, 2, 3, ...n-1};

    checkIsomorphism(0, n1-1, arr, A, B);                                                //check if an isomorphism exists; 
    (n1 != n1 || m1 != m2 || val != 1) ? printf("\nNO!\n") : printf("\nYES!\n");         //print yes, if isomorphism exists, else print no;
	return 0;
}