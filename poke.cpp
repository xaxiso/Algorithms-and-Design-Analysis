#include <iostream>
#include <bits/stdc++.h>
#include <math.h>
using namespace std;

int xp[101] = {0};  //experience
int p[101] = {0};
int a[101] = {0};

int arr[2][101][10101] = {0};

int findMax(int a, int b){
	if(a>b)
		return 1;
	else if(a<b)
		return -1;
	else
		return 0;
}

void swap(int *xp, int *yp){  
    int temp = *xp;  
    *xp = *yp;  
    *yp = temp;  
}

//ratio of attack/potential
void bubblesort(int n){ //potential biggest put front, attack biggest put back
	int i, j, count = 0;
	for (i = n-2; i >= 0; i--){
		for (j = 0; j <= i; j++){
			if(a[j]==0 || p[j]==0){

				if(a[j]==0 && p[j]==0){  //0 0 case
					if(a[j+1] || p[j+1]){
						swap(&a[j], &a[j+1]);
						swap(&p[j], &p[j+1]);
						//printf("%d\n", ++count);
						continue;
					}
				}

				else if(a[j]==0 && a[j+1]==0 && p[j]<p[j+1]){
					swap(&a[j], &a[j+1]);
					swap(&p[j], &p[j+1]);
					continue;
				}

				else if(p[j]==0 && p[j+1]==0 && a[j]>a[j+1]){
					swap(&a[j], &a[j+1]);
					swap(&p[j], &p[j+1]);
					continue;
				}

			}
			
			if((a[j]*p[j+1])>(p[j]*a[j+1])){
				swap(&a[j], &a[j+1]);
				swap(&p[j], &p[j+1]);
			}

			
		}
	}

/*
	printf("\n");
	for (int i = 0; i < n; ++i)
		printf("%d: %d %d\n", i+1, ap[0][i], ap[1][i]);
	*/
}


void arrange(int n, int k){
	int i=0, j=0;
	//if attack same, look for bigger experience

	//base case
	for(int i=0; i<=n; i++){
		for(int j=0; j<=k; j++){
			for(int w = 0; w<=10101; w++){
				if(w==0)
					arr[i%2][j][0]=0;
				else
					arr[i%2][j][w]=-1;
			}
		}
	}

	for (int i=1; i<=n; ++i){
		for(int j=1; j<=k; ++j){
			for(int w=0; w<=10101; ++w){
				//if (w-p[i]>=0)
					if((arr[(i+1)%2][j-1][w-p[i-1]])<0 || (w-p[i-1])<0) //upper left is -1, has nothing in experience
						arr[i%2][j][w] = arr[(i+1)%2][j][w];
					else
						arr[i%2][j][w] = max(arr[(i+1)%2][j-1][w-p[i-1]]+a[i-1]*(w-p[i-1]), arr[(i+1)%2][j][w]);
			}
		}
	}

	
	long long int max = 0;
	for(i=0;i<10101;i++){
		long long int current = arr[n%2][k][i];
		if(current>max)
			max = current;
	}
	printf("%lld", max);
}

int main(){
	int k, n;
	scanf("%d%d", &n, &k);
	for(int i = 0;i<n;i++)
		scanf("%d%d", &a[i], &p[i]);
	bubblesort(n);
	arrange(n, k);
	//ten(n, k);
}


	/*
	//debug
	printf("\n");
	for(i=0;i<n;i++){ //arr
		for(j=0;j<k;j++){
			if(arr[i][j]==0 && j!=0)
				printf("%d  ", arr[i][j]);
			else
				printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	for(i=0;i<n;i++){ //xparr
		for(j=0;j<k;j++){
				printf("%d ", xparr[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	*/

/*
			//first k round needs to retrieve largest max potential(experience)
			if(j==0)
				xparr[i][j]=findMax(xparr[i-1][j], ap[1][i]+xparr[i-1][j-1]);
			else if(arr[i][j]==arr[i-1][j] && i!=0)
				xparr[i][j]=xparr[i-1][j];
			else
				xparr[i][j] = ap[1][i]+xparr[i-1][j-1];
			*/

/*int max = 0;
	while(i<n){
		max+=(ap[0][i]*xp[i]);
		for(j=i+1;j<n;j++){
			xp[j]+=ap[1][i];
		}
		i++;
	}
	printf("%d", max);
	*/

/*else if(arr[i][j]==arr[i-1][j] && i!=0){
				//if(ap[1][i]>xpmax[ap[0][i]])
				//	xpmax[ap[0][i]] = ap[1][i];
				xparr[i][j]=xparr[i-1][j];
			}

			else{
				if(ap[1][i]>xpmax[ap[0][i]]){
					xpmax[ap[0][i]] = ap[1][i];
					xparr[i][j] = ap[1][i]+xparr[i-1][j-1];
				}
				else
					xparr[i][j] = xpmax[ap[0][i]]+xparr[i-1][j-1];
			}*/