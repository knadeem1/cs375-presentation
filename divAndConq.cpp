#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <numeric>//#include <bits/stdc++.h>
// Divide and Conquer implementation of max subarray problem

using namespace std;

int sum(vector<int> arr){
	int arraySum = 0;
	/*for(int i = 0; i < arr->size(); i++){
		arraySum += arr[i];
	}*/
	for(vector<int>::iterator it = arr.begin(); it != arr.end(); ++it){
		arraySum +=*it;
	}
	return arraySum;
}

// return value: (low, high, sum)
vector<int> maxSubArray(int arr[], int low, int high){
	vector<int> retArr(3);
	vector<int> crossArr(3); //A.K.A. retArr
	int mid;
	vector<int> leftArr(3);
	vector<int> rightArr(3);
	int leftSum;
	int rightSum;
	int crossSum;
	if(high == low){ // base case: one element in the array
		crossArr[0] = low;
		crossArr[1] = high;
		crossArr[2] = arr[low];
		return crossArr;
	}
	else{
		mid = (low+high)/2;
		leftArr = maxSubArray(arr, low, mid);
		rightArr = maxSubArray(arr, mid + 1, high);
		crossArr = maxCrossingSubArray(arr, low, mid, high);
		leftSum =  sum(leftArr);//accumulate(leftSum.begin(), leftSum.end(), 0);
		rightSum = sum(rightArr);//accumulate(rightSum.begin(), rightSum.end(), 0);
		crossSum = sum(crossArr);//accumulate(crossSum.begin(), crossSum.end(), 0);
		if(leftSum >= rightSum && leftSum >= crossSum){
			retArr[0] = leftArr[0];
			retArr[1] = leftArr[1];
			retArr[2] = leftArr[2];
			return retArr;
		}
		else if(rightSum >= leftSum && rightSum >= crossSum){
			retArr[0] = rightArr[0];
			retArr[1] = rightArr[1];
			retArr[2] = rightArr[2];
			return retArr;
		}
		else{
			retArr[0] = rightArr[0];
			retArr[1] = rightArr[1];
			retArr[2] = rightArr[2];
			return retArr;
		}
	}
}


// CLI for compiling and linking:
int main(int argc, char * argv[]){
	vector<int> arr;
	// parse input
	//if(argc != 3) cout<<"ERROR: wrong input format\n";
	/*ifstream file(argv[1]);
	string line;
	int size;
	int n;
	file.is_open();
	line = "";
	while(getline(file, line)){
		//int a = stoi(line);
		arr.push_back(line);//a);
	}
	file.close();
	size = arr.size();
	*/
	int n;
	string line;
	ifstream file(argv[1]);
	while(file >> n){
		arr.push_back(n);
	}
	//maxSubArray(arr, 1, n);
	cout << sum(arr) << endl;
	return 0;
}
