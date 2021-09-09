#include <bits/stdc++.h> 
using namespace std;

long long int arr[5000000];
long long int upd[5000000];
long long int loc[5000000];

struct node { 
	long long int sum, prefixsum, suffixsum, maxsum; 
}; 

node tree[5000000]; 

void build(long long int start, long long int n, long long int index) { 
	//leaf node 
	if (start == n) { 
		tree[index].sum = arr[start]; 
		tree[index].prefixsum = arr[start]; 
		tree[index].suffixsum = arr[start]; 
		tree[index].maxsum = arr[start]; 
	}

	else { 
		long long int mid = (start + n) / 2; 
		
		//left subtree 
		build(start, mid, 2 * index + 1); 
		
		//right subtree 
		build(mid + 1, n, 2 * index + 2); 

		tree[index].sum = tree[2 * index + 1].sum + tree[2 * index + 2].sum; 

		tree[index].prefixsum = max(tree[2 * index + 1].prefixsum, tree[2 * index + 1].sum + tree[2 * index + 2].prefixsum); 

		tree[index].suffixsum = max(tree[2 * index + 2].suffixsum, tree[2 * index + 2].sum + tree[2 * index + 1].suffixsum); 

		tree[index].maxsum = max(tree[index].prefixsum, max(tree[index].suffixsum, max(tree[2 * index + 1].maxsum, max(tree[2 * index + 2].maxsum, tree[2 * index + 1].suffixsum + tree[2 * index + 2].prefixsum)))); 
	} 
} 


void update(long long int index, long long int start, long long int n, long long int idx, long long int value) { 
	// leaf
	if (start == n) { 
		tree[index].sum = value; 
		tree[index].prefixsum = value; 
		tree[index].suffixsum = value; 
		tree[index].maxsum = value; 
	}

	else {
		long long int mid = (start + n) / 2; 

		// if node to be updated is in left subtree 
		if (idx <= mid) 
			update(2 * index + 1, start, mid, idx, value); 
		
		// if node to be updated is in right subtree 
		else
			update(2 * index + 2, mid + 1, n, idx, value); 

		tree[index].sum = tree[2 * index + 1].sum + tree[2 * index + 2].sum; 

		tree[index].prefixsum = max(tree[2 * index + 1].prefixsum, tree[2 * index + 1].sum + tree[2 * index + 2].prefixsum); 

		tree[index].suffixsum = max(tree[2 * index + 2].suffixsum, tree[2 * index + 2].sum + tree[2 * index + 1].suffixsum); 

		tree[index].maxsum = max(tree[index].prefixsum, max(tree[index].suffixsum, max(tree[2 * index + 1].maxsum, max(tree[2 * index + 2].maxsum, tree[2 * index + 1].suffixsum + tree[2 * index + 2].prefixsum)))); 
	} 
} 


node query(long long int index, long long int start, long long int n, long long int l, long long int r) { 
	node result; 
	result.sum = result.prefixsum = result.suffixsum = result.maxsum = INT_MIN; 

	// overlap of range 
	if (l <= start && n <= r) 
		return tree[index]; 

	long long int mid = (start + n) / 2; 

	// right subtree 
	if (l > mid) 
		return query(2 * index + 2, mid + 1, n, l, r); 
		
	// left subtree	 
	if (r <= mid) 
		return query(2 * index + 1, start, mid, l, r); 

	node left = query(2 * index + 1, start, mid, l, r); 
	node right = query(2 * index + 2, mid + 1, n, l, r); 

	// finding the maximum and returning it 
	result.sum = left.sum + right.sum; 
	result.prefixsum = max(left.prefixsum, left.sum + right.prefixsum); 
							
	result.suffixsum = max(right.suffixsum, right.sum + left.suffixsum); 
	result.maxsum = max(result.prefixsum, max(result.suffixsum, max(left.maxsum, max(right.maxsum, left.suffixsum + right.prefixsum)))); 

	return result; 
} 

int main() {
	long long int N, Q;
	scanf("%lld	%lld", &N, &Q);
	for (long long int i = 0; i < N; ++i)
		scanf("%lld", &arr[i]);
	for (long long int i = 0; i < Q; ++i)
		scanf("%lld%lld", &loc[i], &upd[i]);

	build(0, N - 1, 0);

	if((query(0, 0, N-1, 0, N-1).maxsum)<=0)
			printf("%d\n", 0);
		else
			printf("%lld\n", query(0, 0, N-1, 0, N-1).maxsum);

	for (long long int i = 0; i < Q; ++i){
		update(0, 0, N-1, loc[i]-1, upd[i]);
		if((query(0, 0, N-1, 0, N-1).maxsum)<=0)
			printf("%d\n", 0);
		else
			printf("%lld\n", query(0, 0, N-1, 0, N-1).maxsum);
	}

	return 0; 
}