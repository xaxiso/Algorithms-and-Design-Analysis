#include <iostream>
#include <bits/stdc++.h>
#include <queue>
#include <limits.h>
#include <vector>
#include <list>
#include <utility>
#include <unistd.h>
using namespace std;
#define MAXN 200100

vector<int> adj[MAXN];
int visited[MAXN] = {0};
vector<int> priority;
int num[MAXN] = {0};
vector<int>::iterator it1;
vector<int>::iterator it2;
vector<int> v1(1003);
vector<int> v2(1003);

vector<int> reach[MAXN];

int current1, current2, flag = 0;

void DFS(int v, int n){
	if(visited[v]==1 || visited[v]==2) return;
	reach[v].push_back(v);
	visited[v] = 1;

	for(int i=0;i<adj[v].size();i++){
		if(!visited[adj[v][i]]){
			// printf("%d\n", adj[v][i]);
			DFS(adj[v][i], n);
		}

		int size1 = reach[v].size(), size2 = reach[adj[v][i]].size();
		int index1 = 0, index2 = 0;

		vector<int> tmp;
		for(int j=0;j<size1;j++) tmp.push_back(reach[v][j]);
		reach[v].clear();

		for(int k=1;k<=500;k++){
			current1 = tmp[index1];
			current2 = reach[adj[v][i]][index2];
			flag = 0;

			if(index1==size1 && index2==size2) break;

			else if(index1<size1 && index2==size2){
				reach[v].push_back(current1);
				index1++;
				flag = 1;
			}
			else if(index1==size1 && index2<size2){
				reach[v].push_back(current2);
				index2++;
				flag = 1;
			}

			if(current1 == current2 && flag==0){
				reach[v].push_back(current2);
				index1++, index2++;
			}
			else if(current1<current2 && flag==0){
				reach[v].push_back(current1);
				index1++;
			}
			else if(current1>current2 && flag==0){
				reach[v].push_back(current2);
				index2++;
			}
		}

	}

	visited[v] = 2;
}

void DFS_start(int n){
	for(int i=1;i<=n;i++) DFS(i, n);

	// for (int i = 1; i <= n; i++){
	// 	printf("vertex %d", i);
	// 	for(int j=0 ; j < reach[i].size(); j++)
	// 		printf(" -> %d", reach[i][j]);
	// 	printf("\n");
	// }
}

void calculate(int x, int y, int n){
	double result = 0;

	it1 = set_union(reach[x].begin(), reach[x].end(), reach[y].begin(), reach[y].end(), v1.begin());
	if(it1-v1.begin()<500) v1.resize(it1-v1.begin());
	else v1.resize(500);
	// v1.resize(it1-v1.begin());

	it2 = set_intersection(reach[x].begin(), reach[x].end(), reach[y].begin(), reach[y].end(), v2.begin());
	if(it2-v2.begin()<500) v2.resize(it2-v2.begin());
	else v2.resize(500);
	// v2.resize(it2-v2.begin());

	// printf("inter: %lf, uni: %lf\n", (double)(v2.size()), (double)v1.size());
	result = (double)(v2.size())/(double)(v1.size());

	printf("%lf\n", result);
}

int main(int argc, char const *argv[])
{
	int n, m, q, x, y, temp, temp2;
	scanf("%d%d%d", &n, &m, &q);

	for(int i=1;i<=n;i++) priority.push_back(i);

	srand(3000);
	random_shuffle(priority.begin(), priority.end());

	// for(int i=1;i<=n;i++)
	// 	printf("priority[%d]: %d\n", i, priority[i]);
	// printf("\n");

	for(int i=1;i<=n;i++)
		num[priority[i]]=i;

	// for(int i=1;i<=n;i++)
	// 	printf("num[%d]: %d\n", i, num[i]);

	for(int i=1;i<=m;i++){
		scanf("%d%d", &temp, &temp2);
		adj[priority[temp]].push_back(priority[temp2]);
	}

	DFS_start(n);

	for(int i=1;i<=q;i++){
		scanf("%d%d", &x, &y);
		calculate(priority[x], priority[y], n);
	}

	return 0;
}