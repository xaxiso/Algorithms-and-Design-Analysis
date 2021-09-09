#include <iostream>
#include <stdio.h> 
#include <stdlib.h> 
#include <map> 
#include <iterator>
#include <vector>
#include <list>
#include <utility>
#include <bits/stdc++.h>
#include <cstdlib>
#define MAXN 2400000
#define ll long long int
using namespace std;

map<ll, ll> songmap[MAXN];
pair<ll, ll> p;
map<ll, ll>::iterator it;
vector<ll> adj[MAXN];

ll visited[MAXN] = {0};
ll dp[MAXN] = {0};

ll weight[MAXN] = {0};
ll songID[MAXN] = {0};

bool derped = false;
ll idx = 0;
ll final = 0;

void reset(ll n){
	idx+=2;
	for(int i = 1; i<=n;i++) songmap[i].clear();
	for(ll i = 0; i<=idx; i++){
		adj[i].clear();
		visited[i] = 0;
		dp[i] = 0;
		weight[i] = 0;
		songID[i] = 0;
	}
	derped = false;
	idx = 0;
	final = 0;
}

void DFS(ll V){
	ll diff = 0;
	visited[V] = 1;
	// printf("visited index: %lld\n", V);
	if(adj[V].size() == 0){
		dp[V] = 0;
	}
	for(int i=0 ; i<adj[V].size() ; i++){ //*it == adj[][]
		if(visited[adj[V][i]] == 0) DFS(adj[V][i]);
		else if(visited[adj[V][i]] == 1 && !derped){
			printf("LoveLive!\n");
			// printf("index: %lld -> index: %lld\n", *it, V);
			derped = true;
			return;
		}

		if(songID[V] == songID[adj[V][i]]){
			diff = abs(weight[adj[V][i]] - weight[V]);
			dp[V] = max(dp[V], diff+dp[adj[V][i]]);
			// printf("diff = weight[%lld]: %lld - weight[%lld]: %lld = %lld || dp[%lld] = %lld\n", *it, weight[*it], V, weight[V], diff, V, dp[V]);
		}
		else{
			dp[V] = max(dp[V], 1+dp[adj[V][i]]);
			// printf("different songID || dp[%lld] = %lld\n", V, dp[V]);
		}
	}
	// final = V;
	// printf("final: %lld\n", V);
	visited[V] = 2;
}

void longest(ll n, ll m){
	ll result = 0;

	for (ll i = 0; i<=idx; ++i)
		if(visited[i] == 0 && !derped) DFS(i);
	//dp[final]++;
	
	if(!derped){
		for(ll i = 0;i<=idx; ++i) result = max(result, dp[i]);
		printf("%lld\n", result);
	}
}

void rit(ll &in) {
	char c;
		while(!isdigit(c=getchar_unlocked()));
		in = c - '0';
		while(isdigit(c=getchar_unlocked())) in = in*10 + c-'0';
}

int main(){
	ll t;
	rit(t);

	for(int k = 1; k <=t; k++){
		ll n, m, s1, p1, s2, p2, a;

		// printf("\nWORKING testcase #%d\n", k);
		rit(n);
		rit(m);

		for(ll i = 1;i<=n;++i){
			rit(a);
			songmap[i].insert(make_pair(0, idx)); //songmap[1][1]==idx
			weight[idx] = 0, songID[idx] = i;
			idx++;

			songmap[i].insert(make_pair(a, idx));
			weight[idx] = a, songID[idx] = i;
			idx++;
		}

		for (ll i = 0; i < m; i++){
			rit(s1);
			rit(p1);
			rit(s2);
			rit(p2);
			ll tmp1, tmp2;
			if((it = songmap[s1].find(p1)) == songmap[s1].end()){ //map.end == found nothing
				songmap[s1].insert(make_pair(p1, idx));
				tmp1 = idx;
				weight[idx] = p1;
				songID[idx] = s1;
				idx++;
			}
			else
				tmp1 = it->second;
			if((it = songmap[s2].find(p2)) == songmap[s2].end()){
				songmap[s2].insert(make_pair(p2, idx));
				tmp2 = idx;
				weight[idx] = p2;
				songID[idx] = s2;
				idx++;
			}
			else
				tmp2 = it->second;
			adj[tmp1].push_back(tmp2);
		}

		ll temp;
		for(ll i = 1;i<=n;i++){
			for(auto it = songmap[i].begin(); it!=songmap[i].end();++it){
				if(it == songmap[i].begin())
					temp = it->second;
				else{
					adj[temp].push_back(it->second);
					temp = it->second;
				}
			}
		}

		// for (ll i = 0; i < idx; i++){
		// 	printf("index %lld", i);
		// 	for(ll j=0 ; j < adj[i].size(); j++)
		// 		printf(" -> %lld", adj[i][j]);
		// 	// for(ll j=0 ; j < adj[i].size(); j++)
		// 	// 	printf(" %lld", songmap[i][adj[i][j]]);
		// 	printf("\n");
		// }

		// // for (ll i = 0; i < idx; ++i) printf("weight[%lld]: %lld\n", i, weight[i]);

		// for(ll i = 1;i <=n; i++){ //i = song, it->first = which note, it->second = index
		// 	for(auto it = songmap[i].begin(); it!=songmap[i].end(); ++it){
		// 		printf("songID: %lld, note: %lld, index: %lld\n", i, it->first, it->second);
		// 		//printf("songmap[%lld][%lld] = index#: %lld\n", i, it->second, songmap[i][it->second]);
		// 	}
		// }

		--idx;
		longest(n, m);
		reset(n);
	}

	return 0;
}