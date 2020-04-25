#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int dp(vector<int> arr, int size){
	int max = INT_MIN;
	int current = 0;
	int start = 0;
	int end = 0;
	int s = 0;

	for(int i=0; i<size; i++){
		current += arr.at(i);
		if(max < current){
			max = current;
			start  = s;
			end = i;
		} if(current<0){
			current = 0;
			s = i+1;
		}
	}
}

int main(int argc, char * argv[]){
	if(argc != 3) cout<<"ERROR: wrong input format\n";
	ifstream file(argv[1]);
	string line;
	int size;
	vector<int> arr;
	file.is_open();
	line = "";
	while(getline(file, line)){
		int a = stoi(line);
		arr.push_back(a);		
	}	

	file.close();

	size = arr.size();
	int max = dp(arr, size);
	return 0;
}
