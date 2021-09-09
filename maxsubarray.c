#include <iostream>
//#include <stdio.h>
//#include <stdlib.h>
//#include <stdbool.h>
#include <cmath>
//#include <limits.h>

long long int arr[100000];
long long int loc[100000];
long long int upd[100000];
long long int sum[100000];

typedef struct Node{
	long long int maxPrefixSum;
	long long int maxSuffixSum;
	long long int totalSum;
	long long int maxSubarraySum;
	long long int data;
	struct Node* left;
	struct Node* right;
}Node;

//struct Node* tree = (struct Node*)malloc(sizeof(1000000));

Node* newNode(long long int data){
  	Node* node = (Node*)malloc(sizeof(node)); 
	node->data = data;

	node->left = NULL;
	node->right = NULL;
	return node;
}

void initialize(Node* root){
	root->maxPrefixSum = root->maxSuffixSum = root->maxSubarraySum = INT_MIN; 
    root->totalSum = INT_MIN;
    Node* leftChild = (Node*)malloc(sizeof(Node));
	Node* rightChild = (Node*)malloc(sizeof(Node));
}

Node* merge(Node* leftChild, Node* rightChild){

	Node* parentNode = (Node*)malloc(sizeof(Node));

	parentNode->maxPrefixSum = fmax(leftChild->maxPrefixSum, leftChild->totalSum + rightChild->maxPrefixSum); 

    parentNode->maxSuffixSum = fmax(rightChild->maxSuffixSum, rightChild->totalSum + leftChild->maxSuffixSum); 
 
    parentNode->totalSum = leftChild->totalSum + rightChild->totalSum;

    if(leftChild->maxSubarraySum >= rightChild->maxSubarraySum)
    	parentNode->maxSubarraySum = leftChild->maxSubarraySum;
    else
    	parentNode->maxSubarraySum = rightChild->maxSubarraySum;
    if(parentNode->maxSubarraySum <= leftChild->maxSuffixSum + rightChild->maxPrefixSum)
    	parentNode->maxSubarraySum = leftChild->maxSuffixSum + rightChild->maxPrefixSum;

	return parentNode;
}

void constructTreeUtil(Node* tree, long long int start, long long int end, long long int index){
   
    /* Leaf Node */
    if (start == end) { 
   
        // single element is covered under this range 
        tree[index].totalSum = arr[start]; 
        tree[index].maxSuffixSum = arr[start]; 
        tree[index].maxPrefixSum = arr[start]; 
        tree[index].maxSubarraySum = arr[start]; 
        return; 
    } 
   
    //recursively build left and right children 
    long long int mid = (start + end) / 2; 
    constructTreeUtil(tree, start, mid, 2*index); 
    constructTreeUtil(tree, mid+1, end, 2*index + 1); 
   
    //merge left and right child into the parent node 
    tree[index] = *(merge(&tree[2 * index], &tree[2 * index + 1])); 
} 

Node* constructTree(int n){
	long long int h = (int)(ceil(log2(n))); //height of tree
	//int x = 2*n;
	long long int maxsize = 2*pow(2,h)-1;
	Node* tree = (Node*)malloc(sizeof(maxsize));
	//long long int tree[maxsize];

	constructTreeUtil(tree, 0, n-1, 1);

	return tree;
}

void update(long long int n, long long int i){
		arr[loc[i]-1] = upd[i];
}

int main(){
	long long int N, Q;
	scanf("%lli	%lli", &N, &Q);
	for (int i = 0; i < N; ++i)
		scanf("%lld", &arr[i]);
	for (int i = 0; i < Q; ++i)
		scanf("%lld%lld", &loc[i], &upd[i]);

	Node* root = newNode(0);
	initialize(root);
	Node* tree = constructTree(N);
	
	//maxsubarray(N, 0);
	
	for (int i = 0; i < Q; ++i){
		update(N, i);
		//maxsubarray(N, i);	
	}
	
}

/*
Node queryUtil(Node* tree, long long int ss, long long int se, long long int qs, long long int qe, long long int index) { 
    // No overlap 
    if (ss > qe || se < qs) { 
   
        // returns a Node for out of bounds condition 
        Node nullNode; 
        return nullNode; 
    } 
   
    // Complete overlap 
    if (ss >= qs && se <= qe) { 
        return tree[index]; 
    } 
   
    // Partial Overlap Merge results of Left  
    // and Right subtrees 
    long long int mid = (ss + se) / 2; 
    Node* left = &(queryUtil(tree, ss, mid, qs, qe, 2 * index)); 
    Node* right = &(queryUtil(tree, mid + 1, se, qs, qe, 2 * index + 1)); 
   
    // merge left and right subtree query results 
    Node res = *(merge(left, right)); 
    return res; 
} 
   
//Returns the Maximum Subarray Sum between start and end 
int query(Node* tree, int start, int end, int n) { 
    Node res = queryUtil(tree, 0, n - 1, start, end, 1); 
    return res.maxSubarraySum; 
}
*/
   
/*
int main() 
{ 
    int arr[] = { 1, 3, -4, 5, -2 }; 
    int n = sizeof(arr) / sizeof(arr[0]); 
   
    // Construct Segment Tree 
    Node* Tree = constructTree(arr, n); 
    int start, end, maxSubarraySum; 
   
    // Answering query 1: 
    start = 0; 
    end = 4; 
    maxSubarraySum = query(Tree, start, end, n); 
    cout << "Maximum Sub-Array Sum between "
         << start << " and " << end 
         << " = " << maxSubarraySum << "\n"; 
   
    // Answering query 2: 
    start = 0; 
    end = 2; 
    maxSubarraySum = query(Tree, start, end, n); 
    cout << "Maximum Sub-Array Sum between "
         << start << " and " << end 
         << " = " << maxSubarraySum << "\n"; 
   
    return 0; 
} 

/*
long long int arr[100000];
long long int loc[100000];
long long int upd[100000];
long long int sum[100000];

long long int max(long long int n1, long long int n2){
	if(n1>=n2)
		return n1;
	else
		return n2;
}

void update(long long int n, int i){
		arr[loc[i]-1] = upd[i];
}

void maxsubarray(long long int size) { 
    long long int currentmax = -2147483648, ultimatemax = 0; 
  
    for (int i = 0; i < size; i++) 
    { 
        ultimatemax = ultimatemax + arr[i]; 
        if (currentmax < ultimatemax) 
            currentmax = ultimatemax;
  
        if (ultimatemax < 0) 
            ultimatemax = 0; 
    }
    if(currentmax<0)
    	printf("%lld\n", 0);
    else
    	printf("%lld\n", currentmax); 
}

long long int maxsubarray(long long int length, int start){
    long long int sum = 0;
    long long int max_sum = arr[0];
    for (int i = start; i < length; ++i)
    {
        sum += arr[i];
        sum = max(0, sum);
        max_sum = max(sum, max_sum);
    }
    if(max_sum<0)
    	printf("%lld\n", 0);
    else
    	printf("%lld\n", max_sum);
}

int main(){
	long long int N, Q;
	scanf("%lli	%lli", &N, &Q);
	for (int i = 0; i < N; ++i)
		scanf("%lld", &arr[i]);
	for (int i = 0; i < Q; ++i)
		scanf("%lld%lld", &loc[i], &upd[i]);
	
	maxsubarray(N, 0);

	for (int i = 0; i < Q; ++i){
		update(N, i);
		maxsubarray(N, i);	
	}
}
*/