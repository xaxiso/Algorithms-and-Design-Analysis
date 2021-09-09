#include <iostream>
#include <bits/stdc++.h>
#include <math.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h>
#include <queue>
using namespace std;
#define MAXN 130

vector<int> Q;
vector<int> Qmax;
int adj[MAXN][MAXN] = {0};
int vdeg[MAXN] = {0};
int matrix[MAXN][MAXN];

void constructGraph(int n, vector<int> &R){
	bool flag[MAXN];
	// for(int i=1;i<=n;i++){
		// printf("row: %d\n", i);
		for(int j=1;j<=n;j++){
			// if(matrix[i][j]==1 && i==j && !flag[j]){
			if(vdeg[j] > 0){
				R.push_back(j);
				//flag[j] = true;
				// printf("matrix[%d][%d]: %d -> ", i, j, R.back());
			}
		}
	// }
	// printf("\n");

	// for(int i=1;i<=n;i++){
	// 	if(vdeg[i])
	// 		R.push_back(i);
	// }
}

void constructAdj(int n){
	for(int i=1;i<=n;i++){
		// printf("row: %d", i);
		for(int j=1;j<=n;j++){
			if((matrix[i][j] + matrix[j][i] + matrix[i][i] + matrix[j][j] == 4) && i!=j){
				adj[i][j] = adj[j][i] = 1;
				vdeg[i]++;
				// printf(" -> %d", j);
			}
		}
		// printf("\n");
	}
}

bool intersection(vector<int> &N, int p){
	for(int i=0;i<N.size();i++){
		if(adj[p][N[i]]==1)
			return true;
	}
	return false;
}

int cmp(int x, int y){
	// if(vdeg[x] == vdeg[y])
		return vdeg[x] > vdeg[y];
	// else
	// 	return x > y; return vdeg[x] > vdeg[y];
}

void ColorSort(vector<int> &R, int C[]){
	vector<int> Cset[MAXN];
	int max_no = 1;
	int kmin = Qmax.size() - Q.size() + 1;
	if(kmin <= 0) kmin = 1;
	int j = 0;
	sort(R.begin(), R.end(), cmp);

	for(int i=0;i<R.size();i++){
		int p = R[i];
		int k = 1;
		// printf("hi\n");
		while(intersection(Cset[k], p)){
			// printf("derp\n");
			k += 1;
		}
		if(k > max_no)
			max_no = k;
		Cset[k].push_back(p);
		if(k<kmin){
			R[j] = R[i];
			j+=1;
		}
	}
	
	//C[j-1] = 0;

	for(int k=kmin;k<=max_no;k++){
		for(int i=(Cset[k].size()-1);i>=0;i--){
			R[j] = Cset[k][i];
			C[j] = k;
			j+=1;
		}
	}
	// printf("hi\n");
	// return;
}

void MaxClique(vector<int> &R, int C[]){
	while(R.size()!=0){
		int idx = R.size() - 1;
		int p = R[idx];
		R.pop_back();
		if(Q.size() + C[idx]>Qmax.size()){
			Q.push_back(p);
			// if(intersection(R, p)){
				// printf("derp\n");
			vector<int> newR;
			for(int i=0;i<R.size();i++){
				if(adj[p][R[i]] == 1)
					newR.push_back(R[i]);
			}
			if(newR.size()!=0){

				int newC[MAXN] = {0};
				ColorSort(newR, newC);
				MaxClique(newR, newC);
			}
			// }
			else if(Q.size() > Qmax.size()) Qmax = Q;
			Q.pop_back();
		}
		else return;
	}
	// return;
}

int main(){
	vector<int> R;
	int C[MAXN] = {0};
	int n, i, j, count=0;
	char temp;
	scanf("%d", &n);
	for (i = 1; i <= n; ++i){
		for (j = 0; j <= n; ++j){
			temp = getchar();
			if(temp=='\n'){
				// count++;
				// printf("count: %d\n", count);
				continue;
			}
			temp-='0';
			// printf("%d\n", temp);
			matrix[i][j]=temp;
		}
	}

	// for(i=1;i<=n;i++){
	// 	printf("row[%d]:", i);
	// 	for(j=1;j<=n;j++){
	// 		printf(" %d", matrix[i][j]);
	// 	}
	// 	printf("\n");
	// }

	constructAdj(n);

	constructGraph(n, R);
	sort(R.begin(), R.end(), cmp);

	ColorSort(R, C);
	MaxClique(R, C);

	bool flag[MAXN] = {false};

	for(int i=0;i<Qmax.size();i++){
		printf("%d ", Qmax[i]);
		flag[Qmax[i]] = true;
		count++;
	}

	for(int i=1;i<=n;i++)
		if(!flag[i]) printf("%d ", i);
	printf("\n");
	return 0;
}