#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <numeric>//#include <bits/stdc++.h>
#include <cstdlib>
#include <cmath>
#include <climits>
#include <limits>
#include <chrono>
// Divide and Conquer implementation of max subarray problem

using namespace std;
using namespace std::chrono;

int max(int a, int b){ return (a>b)? a:b;}
int max(int a, int b, int c) { return max(max(a,b),c);}
int maxCrossingSum(vector<int> arr, int low, int mid, int high) 
{ 
    // Include elements on left of mid. 
    int sum = 0; 
    int left_sum = INT_MIN; 
    for (int i = mid; i >= low; i--) 
    { 
        sum = sum + arr[i]; 
        if (sum > left_sum) 
          left_sum = sum; 
    } 
    // Include elements on right of mid 
    sum = 0; 
    int right_sum = INT_MIN; 
    for (int j = mid+1; j <= high; j++) 
    { 
        sum = sum + arr[j]; 
        if (sum > right_sum) 
          right_sum = sum; 
    }
	/*cout << "low: " << low << endl;
	cout << "mid: " << mid << endl;
	cout << "high: " << high << endl;*/
    // Return sum of elements on left and right of mid 
    // returning only left_sum + right_sum will fail for [-2, 1] 
    return max(left_sum + right_sum, left_sum, right_sum); 
}

int maxSubArraySum(vector<int> arr, int low, int high){
	if(low == high){
		return arr.at(low);
	}
	int mid = (low+high)/2;
	int leftsum = maxSubArraySum(arr, low, mid);
	int rightsum = maxSubArraySum(arr, mid + 1, high);
	int sum3 = maxCrossingSum(arr, low, mid, high);
	if(max(leftsum, rightsum, sum3) == leftsum){
		cout << "low: " << low << " mid: " << mid << endl; 
	}
	else if(max(leftsum, rightsum, sum3) == rightsum)
		cout << "mid+1: " << mid+1 << " high: " << high << endl;
	else
		cout << "low: " << low << " high: " << high << endl;
	return max(maxSubArraySum(arr, low, mid),
				maxSubArraySum(arr, mid + 1, high),
				maxCrossingSum(arr, low, mid, high));
}

int sum(vector<int> arr){
	int arraySum = 0;
	for(vector<int>::iterator it = arr.begin(); it != arr.end(); ++it){
		arraySum +=*it;
	}
	return arraySum;
}

vector<int> maxCrossingSubArray(vector<int> &arr, int low, int mid, int high){
	vector<int> retArr(3);
	int leftSum = -INT_MIN;
	int rightSum = -INT_MIN;
	int sum = 0;
	int maxLeft;
	int maxRight;
	for(int i = mid; i > low; i--){
			sum += arr[i];
			if(sum > leftSum){
				leftSum = sum;
				maxLeft = i;
			}
	}
	sum = 0;
	for(int j = mid + 1; j < high; j++){
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
		leftSum = sum(leftArr);
		rightSum = sum(rightArr);
		crossSum = sum(crossArr);
		if(leftSum > rightSum && leftSum > crossSum){
			retArr[0] = leftArr[0];
			retArr[1] = leftArr[1];
			retArr[2] = leftArr[2];
			//retArr = leftArr;
			//cout << "roast chicken" << endl;
			//cout << "left index: " << leftArr[0] << endl;
			return retArr;//return leftArr;//return retArr;
		}
		else if(rightSum > leftSum && rightSum > crossSum){
			retArr[0] = rightArr[0];
			retArr[1] = rightArr[1];
			retArr[2] = rightArr[2];
			//retArr = rightArr;
			//cout << "right index: " << rightArr[0] << endl;
			//cout << "soy sauce crabs" << endl;
			return retArr;//return rightArr;//return retArr;
		}
		else{
			retArr[0] = crossArr[0];
			retArr[1] = crossArr[1];
			retArr[2] = crossArr[2];
			//retArr = crossArr;
			//cout << "sea urchin" <<endl;
			return retArr;//return crossArr;//return retArr;
		}
		/*if(max(rightSum, leftSum, crossSum) == rightSum){
			return rightArr;
		}
		else if(max(rightSum, leftSum, crossSum) == leftSum){
			return leftArr;
		}
		else return crossArr;*/
	}
}
int main(int argc, char * argv[]){
	vector<int> arr;
	int val;
	string line;
	ifstream file(argv[1]);
	while(file >> val){
		arr.push_back(val);
	}
	int maxSum = 0;
	vector<int> retArr(3);
	int n = arr.size(); //just the size of the vector
	auto start = high_resolution_clock::now();
	retArr = maxSubArray(arr, 1, n);//0, n-1); // retArr.size() is n
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(end-start);
	int max = maxSubArraySum(arr, 0, n-1);
	cout<<"MAAAXXXX: "<<max<<endl;
	cout<<"START INDEX = "<<retArr[0]<<", END INDEX = "<<retArr[1]<<endl;
	cout<<"MAX SUM = "<<retArr[2]<<endl;
	cout<<"TIME ELAPSED (ns) = "<<duration.count()<<endl;
	
	return 0;
}
