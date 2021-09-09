#include <iostream>
#include <bits/stdc++.h>
#include <math.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h>
#include <queue>
using namespace std;
#define INF 0x3f3f3f3f

long long int result[2000000];
long long int result2[2000000];

struct path{
	long long int source;
	long long int dest;
	long long int distance;
	long long int danger;

	path(long long int source, long long int dest, long long int distance, long long int danger)
		: source(source), dest(dest), distance(distance), danger(danger)
		{
		}
};

struct compareDistance{
	bool operator()(path const& p1, path const& p2){
		return p1.distance > p2.distance;
	}
};

struct compareDanger{
	bool operator()(path const& p1, path const& p2){
		return p1.danger > p2.danger;
	}
};

priority_queue<path, vector<path>, compareDistance> distanceQ; 
priority_queue<path, vector<path>, compareDanger> dangerQ; 

void distanceQueue(long long int source, long long int dest, long long distance, long long int danger){
        distanceQ.push(path(source, dest, distance, danger));
}

void dangerQueue(long long int source, long long int dest, long long distance, long long int danger){
        dangerQ.push(path(source, dest, distance, danger));
}

struct AdjListNode{ 
	//long long int src;
    long long int dest; 
    long long int distance;
    long long int danger; 
    struct AdjListNode* next; 
}; 

struct AdjList{ 
    struct AdjListNode *head;
}; 
 
struct Graph{
    long long int V; 
    struct AdjList* array; 
};

struct Graph* createGraph(long long int V){ 
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph)); 
    graph->V = V; 
  
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList)); 
  
    for (long long int i = 0; i < V; ++i) 
        graph->array[i].head = NULL; 
  
    return graph; 
}

struct AdjListNode* newAdjListNode(long long int dest, long long int distance, long long int danger){ 
    struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode)); 
    newNode->dest = dest; 
    newNode->distance = distance;
    newNode->danger = danger; 
    newNode->next = NULL; 
    return newNode; 
}

void addEdge(struct Graph* graph, long long int src, long long int dest, long long int distance, long long int danger){
    struct AdjListNode* newNode = newAdjListNode(dest, distance, danger); 
    newNode->next = graph->array[src].head; 
    graph->array[src].head = newNode; 
  
    newNode = newAdjListNode(src, distance, danger); 
    newNode->next = graph->array[dest].head; 
    graph->array[dest].head = newNode; 
} 

void dijkstra(struct Graph* graph, long long int n, long long int start, long long int final, long long int l){
//FIND MIN DANGER
	bool flag[200000] = {false};
	for (long long int i = 0; i <= n; ++i) result[i] = LLONG_MAX;
	result[start] = 0;
	struct AdjListNode* current = graph->array[start].head;
	flag[current->dest] = true;
	while(current!=NULL){  //check if enpty
		dangerQueue(start, current->dest, current->distance, current->danger);
		// printf("QUEUE - vertex: %lld to vertex: %lld - distance: %lld, danger: %lld\n", start, current->dest, current->distance, current->danger);
		current = current->next;
	}
	while(!dangerQ.empty()){
		path u = dangerQ.top();
		dangerQ.pop();
		if(flag[u.source]) continue;
		flag[u.source] = true;
		printf("POP - vertex: %lld to vertex: %lld - distance: %lld, danger: %lld\n", u.source, u.dest, u.distance, u.danger);

		if(result[u.dest] > max(result[u.source],u.danger)){
			result[u.dest] = max(result[u.source],u.danger);
			dangerQueue(u.source, u.dest, u.distance, result[u.dest]);
			printf("QUEUE - vertex: %lld to vertex: %lld - distance: %lld, danger: %lld\n", u.source, u.dest, u.distance, result[u.dest]);

			for(long long int j = 0;j<n;j++)
				printf("result[%lld]: %lld\n", j, result[j]);
		
			printf("CHOSEN -- source: %lld, dest: %lld, distance: %lld, danger: %lld\n", u.source, u.dest, u.distance, u.danger);

			current = graph->array[u.dest].head;
			while(current!=NULL){  //check if enpty
				// if(!flag[current->dest]){
					dangerQueue(u.dest, current->dest, current->distance, current->danger);
					printf("QUEUE - vertex: %lld to vertex: %lld - distance: %lld, danger: %lld\n", u.dest, current->dest, current->distance, current->danger);
				// }
				current = current->next;
			}
		}
		printf("------------------VERTEX FINISHED---------------------\n\n");
	}
	printf("FINISHED DANGER -- minDanger: %lld\n\n\n\n", result[final]);


//FIND MIN DISTANCE
	//result[final] = l;
	bool flag2[200000] = {false};
	for (long long int i = 0; i <= n; ++i) result2[i] = LLONG_MAX;
	result2[start] = 0;
	current = graph->array[start].head;
	flag2[current->dest] = true;
	while(current!=NULL){ 
		distanceQueue(start, current->dest, current->distance, current->danger);
		printf("QUEUE - vertex: %lld to vertex: %lld - distance: %lld, danger: %lld\n", start, current->dest, current->distance, current->danger);
		current = current->next;
	}

	while(!distanceQ.empty()){
		path u = distanceQ.top();
		distanceQ.pop();
		if(flag2[u.source]) continue;
		flag2[u.source] = true;
		printf("POP - vertex: %lld to vertex: %lld - distance: %lld, danger: %lld\n", u.source, u.dest, u.distance, u.danger);

		// printf("%lld <= %lld\n", u.danger, result[final]);
		if(u.danger<=result[final] && (result2[u.dest]>(result2[u.source]+u.distance))){
			result2[u.dest]=(result2[u.source]+u.distance);
			distanceQueue(u.source, u.dest, result2[u.dest], u.danger);
			printf("QUEUE - vertex: %lld to vertex: %lld - distance: %lld, danger: %lld\n", u.source, u.dest, result2[u.dest], u.danger);

			for(long long int j = 0;j<n;j++)
				printf("result2[%lld]: %lld\n", j, result2[j]);

			printf("CHOSEN -- source: %lld, dest: %lld, distance: %lld, danger: %lld\n", u.source, u.dest, u.distance, u.danger);

			current = graph->array[u.dest].head;
			while(current!=NULL){
				// if(!flag2[current->dest]){
					distanceQueue(u.dest, current->dest, current->distance, current->danger);
					printf("QUEUE - vertex: %lld to vertex: %lld - distance: %lld, danger: %lld\n", u.dest, current->dest, current->distance, current->danger);
				// }
				current = current->next;
			}
		}

		printf("------------------VERTEX FINISHED---------------------\n\n\n");
	}
	for(long long int i = 0;i<n;i++){
		if(result2[i]!=0)
			printf("result2[%lld]: %lld\n", i, result2[i]);
	}
	printf("FINISHED DISTANCE -- newMinDistance: %lld\n\n\n", result2[final]);

	printf("%lld %lld", result2[final], result[final]);
}

int main (){ 
	long long int n, m, s, t, x, y, d, l;
	scanf("%lld%lld%lld%lld", &n, &m, &s, &t);
	struct Graph* graph = createGraph(n);

	for (int i = 0; i < m; ++i){
		scanf("%lld%lld%lld%lld", &x, &y, &d, &l);
		addEdge(graph, x, y, d, l);
	}

	dijkstra(graph, n, s, t, l);
	
	return 0; 
}