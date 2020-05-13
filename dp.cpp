// dp.cpp contains methods: void dp, int main
// dp.cpp serves as the implementation of the dynamic programming solution to the maximum subarray problem.
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <climits>
#include <chrono>

using namespace std;
using namespace std::chrono;

/*
Function used to solve the maximum subarray problem. Takes in array as well as the size of the array(or the size of the problem n). The goal is to use dynamic programming to obtain a subarray that has the largest sum of elements of any other subarray in the problem.
This function also keeps track of the runtime of the algorithm using the chrono library, keeping a timestamp of when the function begins running and ends.
*/
void dp(vector<int> arr, int size){
	// mark the beginning of the algorithm runtime
	auto begin = high_resolution_clock::now();
	int max = INT_MIN; // variable for max sum initialized to small value
	int current = 0; // current max temp variable
	int start = 0; // beginning index of max subarray initialized to 0
	int end = 0; // ending index of max subarray initialized to 0
	int s = 0; // temp variable to keep track of index

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
	// mark the end of the algorithm runtime
	auto stop = high_resolution_clock::now();
	// calcualte duration of the runtime
	auto duration = duration_cast<nanoseconds>(stop-begin);

	cout<<"START INDEX = "<<start<<", END INDEX = "<<end<<endl;
	cout<<"MAX SUM = "<<max<<endl;
	cout<<"TIME ELAPSED (ns) = "<<duration.count()<<endl;
	//return max;
}
/*
Serves as driver for the dynamic programming solution to the maximum subarray problem. Takes in two input files <inputfile>.txt and <output>.txt
It parses the input file to obtain an array of integers(stored in a vector). dp() is then called, passing in this input vector and its size(number of elements)
*/
int main(int argc, char * argv[]){
	if(argc != 2) cout<<"ERROR: wrong input format\n";
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
	dp(arr, size);
	return 0;
}
