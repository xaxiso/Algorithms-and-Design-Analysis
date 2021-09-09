#include <bits/stdc++.h>
#include <map>
using namespace std;

int main(){
	map<int, char*> name_map;

	name_map[1] = "Tom\0";
	name_map[2] = "Max\0";
	name_map[3] = "Mark\0";
	name_map[4] = "John\0";
	name_map[5] = "Patrik\0";

	map<int, char*>::iterator it = name_map.find(5);
	name_map.erase(it);
	cout<<"key found = "<< it->second <<endl;

	name_map.insert(pair<int, char*>(6, "Jauly\0"));

	cout<<"map size = "<<name_map.size()<<endl;
	cout<<"is empty = "<<name_map.empty()<<endl;

	for(it = name_map.begin(); it!= name_map.end();it++)
		printf("%d -> %s\n", it->first, it->second);
		//cout<<it->first<<" -> "<<it->second<<endl;

	return 0;
}