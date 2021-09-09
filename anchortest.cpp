#include <iostream>
#include <math.h>
#include <bits/stdc++.h>
using namespace std;

long long int s[4];
long long int e[200100];

long long int hour = 0;
long long int mem[2000000] = {0};

long long int greedy(long long int n){
	long long int i=1, count=0;
	long long int s1, s2, s3, s1s2, s1s3, s2s3, s1s2s3;
	s1 = s2 = s3 = s1s2 = s1s3 = s2s3 = s1s2s3 = 0;

	while(e[i]<=s[1] && i<=n){
			s1++;
			i++;
	}
	////sub("s[1]: %lld, s[2]: %lld, s[3]: %lld, s[1]+s[2]: %lld, s[1]+s[3]: %lld, s[2]+s[3]: %lld, s[1]+s[2]+s[3]: %lld\n", s1, s2, s3, s1s2, s1s3, s2s3, s1s2s3);

	while(e[i]<=s[2] && i<=n){
			s2++;
			i++;
	}
	////sub("s[1]: %lld, s[2]: %lld, s[3]: %lld, s[1]+s[2]: %lld, s[1]+s[3]: %lld, s[2]+s[3]: %lld, s[1]+s[2]+s[3]: %lld\n", s1, s2, s3, s1s2, s1s3, s2s3, s1s2s3);
	
	if((s[1]+s[2])<=s[3]){  //if s1+s2 <= s3 then put it all in s1s2
		while(i<=n && e[i]<=(s[1]+s[2])){
				s1s2++;
				i++;

		}
		////sub("e[i]<=s1+s2 -- s[1]: %lld, s[2]: %lld, s[3]: %lld, s[1]+s[2]: %lld, s[1]+s[3]: %lld, s[2]+s[3]: %lld, s[1]+s[2]+s[3]: %lld\n", s1, s2, s3, s1s2, s1s3, s2s3, s1s2s3);

		while(i<=n && e[i]>(s[1]+s[2]) && e[i]<=s[3]){
				s3++;
				i++;
		}
		////sub("e[i]>s1+s2  -- s[1]: %lld, s[2]: %lld, s[3]: %lld, s[1]+s[2]: %lld, s[1]+s[3]: %lld, s[2]+s[3]: %lld, s[1]+s[2]+s[3]: %lld\n", s1, s2, s3, s1s2, s1s3, s2s3, s1s2s3);
	}
	else{
		while(e[i]<=s[3] && i<=n){
				s3++;
				i++;
		}

		while(e[i]<=(s[1]+s[2]) && i<=n){
				s1s2++;
				i++;
		}
	}
	////sub("s[1]: %lld, s[2]: %lld, s[3]: %lld, s[1]+s[2]: %lld, s[1]+s[3]: %lld, s[2]+s[3]: %lld, s[1]+s[2]+s[3]: %lld\n", s1, s2, s3, s1s2, s1s3, s2s3, s1s2s3);

	while(e[i]<=(s[1]+s[3]) && i<=n){
			s1s3++;
			i++;
	}
	////sub("s1+s3 -- s[1]: %lld, s[2]: %lld, s[3]: %lld, s[1]+s[2]: %lld, s[1]+s[3]: %lld, s[2]+s[3]: %lld, s[1]+s[2]+s[3]: %lld\n", s1, s2, s3, s1s2, s1s3, s2s3, s1s2s3);


	while(e[i]<=(s[2]+s[3]) && i<=n){
			s2s3++;
			i++;
	}
	////sub("s[1]: %lld, s[2]: %lld, s[3]: %lld, s[1]+s[2]: %lld, s[1]+s[3]: %lld, s[2]+s[3]: %lld, s[1]+s[2]+s[3]: %lld\n", s1, s2, s3, s1s2, s1s3, s2s3, s1s2s3);

	while(e[i]<=(s[1]+s[2]+s[3]) && i<=n){
			s1s2s3++;
			i++;
	}
	//sub("start:\ns[1]: %lld, s[2]: %lld, s[3]: %lld, s[1]+s[2]: %lld, s[1]+s[3]: %lld, s[2]+s[3]: %lld, s[1]+s[2]+s[3]: %lld\n\n", s1, s2, s3, s1s2, s1s3, s2s3, s1s2s3);


//divide--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	while(s1s2s3){
		s1s2s3--;
		hour++;
	}
	//sub("s1s2s3--s[1]: %lld, s[2]: %lld, s[3]: %lld, s[1]+s[2]: %lld, s[1]+s[3]: %lld, s[2]+s[3]: %lld, s[1]+s[2]+s[3]: %lld, hour: %lld\n", s1, s2, s3, s1s2, s1s3, s2s3, s1s2s3, hour);

	if((s[1]+s[2])>s[3]){
		while(s1s2){
			if(s3){
				s1s2--;
				s3--;
				hour++;
			}
			else if(s2){
				s1s2--;
				s2--;
				hour++;
			}
			else if(s1){
				s1s2--;
				s1--;
				hour++;
			}
			else if(s3==0 && s2==0 && s1==0){
				s1s2--;
				hour++;
			}
			else
				break;
		}
	}
	//sub("s1s2 -- s[1]: %lld, s[2]: %lld, s[3]: %lld, s[1]+s[2]: %lld, s[1]+s[3]: %lld, s[2]+s[3]: %lld, s[1]+s[2]+s[3]: %lld, hour: %lld\n", s1, s2, s3, s1s2, s1s3, s2s3, s1s2s3, hour);


	while(s2s3){
		if(s1){
			s2s3--;
			s1--;
			hour++;
		}
		else if(s1==0){
			s2s3--;
			hour++;
		}
		else
			break;
	}
	//sub("s2s3 -- s[1]: %lld, s[2]: %lld, s[3]: %lld, s[1]+s[2]: %lld, s[1]+s[3]: %lld, s[2]+s[3]: %lld, s[1]+s[2]+s[3]: %lld, hour: %lld\n", s1, s2, s3, s1s2, s1s3, s2s3, s1s2s3, hour);


	while(s1s3){
		if(s2){
			s1s3--;
			s2--;
			hour++;
		}
		else if(s1){
			s1s3--;
			s1--;
			hour++;
		}
		else if(s1==0 && s2==0){
			s1s3--;
			hour++;
		}
		else
			break;
	}
	//sub("s1s3 -- s[1]: %lld, s[2]: %lld, s[3]: %lld, s[1]+s[2]: %lld, s[1]+s[3]: %lld, s[2]+s[3]: %lld, s[1]+s[2]+s[3]: %lld, hour: %lld\n", s1, s2, s3, s1s2, s1s3, s2s3, s1s2s3, hour);



		////sub("s1s2mem: %lld s3mem: %lld\n", s1s2mem, s3mem);

	if((s[1]+s[2])<=s[3]){ //?????????
		s3+=s1s2;
		//s1s2=0;
	}
	////sub("s[1]: %lld, s[2]: %lld, s[3]: %lld, s[1]+s[2]: %lld, s[1]+s[3]: %lld, s[2]+s[3]: %lld, s[1]+s[2]+s[3]: %lld, hour: %lld\n", s1, s2, s3, s1s2, s1s3, s2s3, s1s2s3, hour);
/*
	if((s[1]+s[2])>s[3]){
		while(s3>s1s2){
			s3--;
			s1s2++;
		}
	}*/

	while(s1>s2 || s2>s3){
		while(s1>s2){
			s1--;
			s2++;
		}
		while(s2>s3){
			s2--;
			s3++;
		}
	}

	long long int s1s2mem = s1s2, s3mem = s3-s1s2;

	//sub("\n");
	//sub("balanced -- s1: %lld, s2: %lld, s3: %lld, s1s2: %lld\n", s1, s2, s3, s1s2);
	//sub("\n");

		
	if((s[1]+s[2])>s[3]){
		s3+=s2;
		s3=s3/2+s3%2;
		//while(s3>s1s2){
		//	s3--;
		//	s1s2++;
		//}
		hour+=s3;
	}

	else if((s[1]+s[2])<=s[3]){
		//sub("s1s2mem: %lld s3mem: %lld\n", s1s2mem, s3mem);
		long long int s2count = s2, s2original = s2;

		s3-=s2;
		s2=0;

		////sub("s1: %lld, s2: %lld, s3: %lld, s1s2: %lld\n", s1, s2, s3, s1s2);

		////sub("s1: %lld, s2: %lld, s3: %lld, s1s2: %lld\n", s1, s2, s3, s1s2);

		//s1s2mem-=s2;
		//s3mem-=s2;
	
		while(s3mem && s2count){
			s3mem--;
			s2count--;
		}
		////sub("s1: %lld, s2: %lld, s3: %lld, s1s2: %lld\n", s1, s2, s3, s1s2);

		s1s2mem-=s2count;

		////sub("s1s2mem: %lld s3mem: %lld\n", s1s2mem, s3mem);
		while(s1s2mem>s3mem){
			s1s2mem--;
			s3mem++;
		}
		//sub("s1s2mem: %lld, s3mem: %lld, s2original: %lld\n", s1s2mem, s3mem, s2original);


		hour+=(s3mem+s2original);
	}
	//sub("final-- s[1]: %lld, s[2]: %lld, s[3]: %lld, s[1]+s[2]: %lld, s[1]+s[3]: %lld, s[2]+s[3]: %lld, s[1]+s[2]+s[3]: %lld, hour: %lld\n", s1, s2, s3, s1s2, s1s3, s2s3, s1s2s3, hour);

	printf("%lld", hour);

}


int main(){
	long long int n;
	scanf("%lld",&n);

	for (int i = 1; i < 4; ++i)
		scanf("%lld", &s[i]);
	
	for (long long int i=1; i <= n; ++i)
		scanf("%lld", &e[i]);

	for(long long int k=1;k<=n;k++){
		if((s[1]+s[2]+s[3])<e[k]){
			printf("-1");
			return 0;
		}
	}

	sort(e+1, e + n + 1);
	sort(s+1, s + 4);

/*
	for (long long int i = 1; i <=3; ++i)
		//sub("%lld ", s[i]);
	//sub("\n");

	for (long long int i = 1; i <=n; ++i)
		//sub("%lld ", e[i]);
	//sub("\n");
	*/

	greedy(n);

	return 0;
}