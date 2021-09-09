#include <array>
#include <iostream>
#include <random>
#include <math.h>
#include <bits/stdc++.h> 
#include <vector>     
using namespace std; 


namespace ada {

class Xoroshiro128 {
 public:
  using result_type = uint32_t;
  static constexpr result_type(min)() { return 0; }
  static constexpr result_type(max)() { return UINT32_MAX; }
  static inline result_type rotl(const result_type x, int k) {
    return (x << k) | (x >> (32 - k));
  }
  Xoroshiro128() : Xoroshiro128(1, 2, 3, 4) {}
  Xoroshiro128(result_type a, result_type b, result_type c, result_type d)
      : s{a, b, c, d} {}
  result_type operator()() {
    const result_type result = rotl(s[0] + s[3], 7) + s[0];
    const result_type t = s[1] << 9;
    s[2] ^= s[0];
    s[3] ^= s[1];
    s[1] ^= s[2];
    s[0] ^= s[3];
    s[2] ^= t;
    s[3] = rotl(s[3], 11);
    return result;
  }

 private:
  std::array<result_type, 4> s;
};

namespace {
int c_lead, c_team;
Xoroshiro128 rng;
}  // namespace

int Init() {
  int n;
  uint32_t s1, s2, s3, s4;
  std::cin >> n >> c_lead >> c_team >> s1 >> s2 >> s3 >> s4;
  rng = Xoroshiro128(s1, s2, s3, s4);
  return n;
}

int GetLeadership() { return uint64_t(rng()) * c_lead >> 32; }

int GetTeamValue() {
  int tmp = int(uint64_t(rng()) * c_team >> 32) + 1;
  return int(c_team / sqrt(tmp));
}

}  // namespace ada


const long long int kN = 20000000;
long long int leadership[20000000], team_value[20000000];
long long int arr[20000000] = {0};
long long int track[20000000] = {0};
long long int mod = pow(10,9)+7;

void teamtotal(long long int n){
	arr[0] = team_value[0];
	for(long long int i = 1; i<n; i++)
		arr[i] = team_value[i]+arr[i-1];
	//printf("test\n");
}

long long int tabulation(long long int n){
	long long int count = 1;
	long long int pos = 0;
	for (long long int i = n-2; i >= 0; i--){
		pos = upper_bound(arr + i + 1, arr + n, leadership[i] + arr[i]) - (arr + i + 1); //cuts off at the index including the prior ones below upper bound

		if((i+pos+2)>n)
			track[i] = 2*track[i+1];
		else
			track[i]=(2*(track[i+1])-track[i+pos+2]);

		if(track[i])
			track[i] = (track[i]+mod)%mod;
		else
			track[i] %= mod;
/*
		if((i+pos+2)>=n)
			printf("i+pos+2 -- index: %lld, track[%lld]: %lld\n", i, i, track[i]);
		else
			printf("pos: %lld, index: %lld, track[%lld]: %lld\n",i+pos+2, i, i, track[i]);
		*/
	}
	return track[0]-track[1];
}

int main() {
	long long int output;
	long long int n = ada::Init(); // Get N
	for (long long int i = 0; i < n; i++){
		leadership[i] = ada::GetLeadership();
		//printf("%lld ", leadership[i]);
	}
	//printf("\n");
	for (long long int i = 0; i < n; i++){
		team_value[i] = ada::GetTeamValue();
		//printf("%lld ", team_value[i]);
	}
	//printf("\n");

	arr[n+1] = 1; //base combination of 1

	track[n] = 1; //imaginary over the last index that's filled
	track[n-1] = 2;

	teamtotal(n);
	//tabulation(n);
	output = tabulation(n);

	if(output<0)
		output = (output+mod)%mod;
	else
		output%=mod;

	printf("%lld", output);
}