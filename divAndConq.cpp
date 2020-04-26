#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <numeric>//#include <bits/stdc++.h>
#include <cstdlib>
#include <cmath>
#include <limits>
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

vector<int> maxCrossingSubArray(vector<int> &arr, int low, int mid, int high){
	vector<int> retArr(3);
	float leftSum = -INFINITY;
	float rightSum = -INFINITY;
	int sum = 0;
	int maxLeft;
	int maxRight;
	for(int i = mid; i >= low; i--){
			sum += arr[i];
			if(sum > leftSum){
				leftSum = sum;
				maxLeft = i;
			}
	}
	sum = 0;
	for(int j = mid + 1; j <= high; j++){
		sum += arr[j];
		if(sum > rightSum){
			rightSum = sum;
			maxRight = j;
		}
	}
	retArr[0] = maxLeft;
	retArr[1] = maxRight;
	retArr[2] = leftSum + rightSum;
	return retArr;
}

// return value: (low, high, sum)
vector<int> maxSubArray(vector<int> &arr, int low, int high){
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
		mid = (low+high);
		mid /= 2;
		leftArr = maxSubArray(arr, low, mid);
		rightArr = maxSubArray(arr, mid + 1, high);
		crossArr = maxCrossingSubArray(arr, low, mid, high);
		leftSum = sum(leftArr);//accumulate(leftSum.begin(), leftSum.end(), 0);
		rightSum = sum(rightArr);//accumulate(rightSum.begin(), rightSum.end(), 0);
		crossSum = sum(crossArr);//accumulate(crossSum.begin(), crossSum.end(), 0);
		if(leftSum >= rightSum && leftSum >= crossSum){
			/*retArr[0] = leftArr[0];
			retArr[1] = leftArr[1];
			retArr[2] = leftArr[2];*/
			//retArr = leftArr;
			cout << "roast chicken" << endl;
			return leftArr;//return retArr;
		}
		else if(rightSum >= leftSum && rightSum >= crossSum){
			/*retArr[0] = rightArr[0];
			retArr[1] = rightArr[1];
			retArr[2] = rightArr[2];*/
			//retArr = rightArr;
			cout << "soy sauce crabs" << endl;
			return rightArr;//return retArr;
		}
		else{
			/*retArr[0] = crossArr[0];
			retArr[1] = crossArr[1];
			retArr[2] = crossArr[2];*/
			//retArr = crossArr;
			cout << "sea urchin" <<endl;
			return crossArr;//return retArr;
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
	int val;
	string line;
	ifstream file(argv[1]);
	while(file >> val){
		arr.push_back(val);
	}
	//int maxSum = 0;
	vector<int> retArr(3);
	retArr = maxSubArray(arr, 1, retArr.size()); // retArr.size() is n
	cout << retArr[0] << endl;
	cout << retArr[1] << endl;
	cout << retArr[2] << endl;
	return 0;
}
