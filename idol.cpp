#include <iostream>
#include <bits/stdc++.h>
#include <math.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h>
#include <queue>
using namespace std;
#define ll long long int
#define MAXN 300000

ll dp[MAXN] = {0};
ll dpnum[MAXN] = {0};
ll flag[MAXN] = {0};
ll temp[MAXN] = {0};
vector<ll>adj[MAXN];
ll num = 0;
ll og = 0;

void rit(ll &in) {
	char c;
		while(!isdigit(c=getchar_unlocked()));
		in = c - '0';
		while(isdigit(c=getchar_unlocked())) in = in*10 + c-'0';
}

void dpDFS(ll v, ll n){
	// if(dp[v]!=0){
	// 	dpnum[v]+=
	// 	DFS(dp[v], n);
	// }
	// else{
		if(adj[v].size()!=0){
			temp[adj[v][0]]--;
			dp[og] = adj[v][0];
			if(temp[adj[v][0]]==0){
				dpnum[og]++;
				dpDFS(adj[v][0], n);
			}
		}
	// }
}

void compression(ll n){
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=n;j++) temp[j] = flag[j];
		og = i;
		dpnum[og]++;
		dpDFS(og, n);
	}
}

void DFS(ll v, ll n){
	// printf("Before: temp[%lld]: %lld -- adj[%lld]: %lld\n", v, temp[v], adj[v][0], temp[adj[v][0]]);
	temp[v]--;

	// printf("TEMP[%lld]: %lld\n", adj[v][0], temp[adj[v][0]]);
	// for(ll i = 1; i <= n; i++) printf("temp[%lld]: %lld\n", i, temp[i]);
	// printf("\n");

	if(temp[v]==0){
		num+=dpnum[v];
		// printf("num: %lld\n", num);
		DFS(dp[v], n);
		return;
	}
	else
		return;
}


void bitch(ll n){
	ll q, x, v;
	rit(q);

	for(ll i=1;i<=q;i++){
		rit(x);
		num = 0;

		for(ll j=1;j<=n;j++) temp[j] = flag[j];

		while(x--){
			rit(v);
			og = v;
			num+=dpnum[og];
			// printf("num: %lld\n", num);
			DFS(dp[og], n);

			// printf("TEMP[%lld]: %lld\n", v, temp[v]);
			// for(ll i = 1; i <= n; i++) printf("temp[%lld]: %lld\n", i, temp[i]);
			// printf("\n");
		}
		printf("%lld\n", num);
	}
}

int main(){
	ll n, second;
	rit(n);

	for(ll i=1;i<=n;i++){
		rit(second);
		adj[i].push_back(second);
		flag[second]++;
	}

	// for (ll i = 1; i <= n; i++){
	// 	printf("index %lld", i);
	// 	for(ll j=0 ; j < adj[i].size(); j++)
	// 		printf(" -> %lld", adj[i][j]);
	// 	printf("\n");
	// }

	// for(ll i = 1; i <= n; i++) printf("flag[%lld]: %lld\n", i, flag[i]);

	compression(n);
	bitch(n);

}