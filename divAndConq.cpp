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
// contains functions maxSubArraySum, maxSubArray, sum, maxCrossingSubArray 
using namespace std;
using namespace std::chrono;
//
int max(int a, int b){ return (a>b)? a:b;}
int max(int a, int b, int c) { return max(max(a,b),c);}

/*
Serves as the combining portion of the divide and conquer algorithm, taking in an array, a low, middle, and high index, then returns the maximum sum of a subarray crossing these indices, first summing up the left and right side, then obtaining the max of the left array, right array, and both left and right arrays added together. Returns the maximum sum as an int.
*/
int maxCrossingSum(vector<int> arr, int low, int mid, int high) 
{ 
    // Include elements on left of mid. 
    int sum = 0; // max sum initialized to 0
    int left_sum = INT_MIN; // sum of left side initialized to small value
    for (int i = mid; i >= low; i--) 
    { 
        sum = sum + arr[i]; // keep adding array values between low and mid
        if (sum > left_sum) 
          left_sum = sum; 
    } 
    // Include elements on right of mid 
    sum = 0; // max sum initialized to 0
    int right_sum = INT_MIN; // sum of right array initialized to small value
    for (int j = mid+1; j <= high; j++) 
    { 
        sum = sum + arr[j]; // keep summing array values between mid+1 and high
        if (sum > right_sum) 
          right_sum = sum; 
    }
	/*cout << "low: " << low << endl;
	cout << "mid: " << mid << endl;
	cout << "high: " << high << endl;*/
    // Return sum of elements on left and right of mid 
    return max(left_sum + right_sum, left_sum, right_sum); 
}

/*
The "divide" portion of the divide and conquer algorithm. Recursively breaks down the array into smaller subarrays and obtains a final maximum subarray by calling maxCrossingSum and returning the maximum of the left max subarray, right max subarray, and the max crossing subarray.
*/
int maxSubArraySum(vector<int> arr, int low, int high){
	if(low == high){ // base case: if the array is of size 1
		return arr.at(low);
	}
	int mid = (low+high)/2; // find middle index
	int leftsum = maxSubArraySum(arr, low, mid); // find maximum left sum
	int rightsum = maxSubArraySum(arr, mid + 1, high); // maximum right sum
	int sum3 = maxCrossingSum(arr, low, mid, high); // maximu crossing sum
	if(max(leftsum, rightsum, sum3) == leftsum){
		cout << "low: " << low << " mid: " << mid << endl; 
	}/*
	else if(max(leftsum, rightsum, sum3) == rightsum)
		cout << "mid+1: " << mid+1 << " high: " << high << endl;
	else
		cout << "low: " << low << " high: " << high << endl;*/
	return max(maxSubArraySum(arr, low, mid),
				maxSubArraySum(arr, mid + 1, high),
				maxCrossingSum(arr, low, mid, high));
}

/* sums up vector values
Takes in a vector as a parameter and returns the sum of its elements.
*/
int sum(vector<int> arr){
	int arraySum = 0; // initialize sum to 0
	for(vector<int>::iterator it = arr.begin(); it != arr.end(); ++it){
		arraySum +=*it; // continue adding values using iterator
	}
	return arraySum;
}

/*
The "combine" portion of the divide and conquer algorithm, taking in an array, a low, middle, and high index, then returns the maximum sum of a subarray crossing these indices, first summing up the left and right side, then obtaining the max of the left array, right array, and both left and right arrays added together. Returns the maximum crossing subarray, rather than an integer value.
*/

vector<int> maxCrossingSubArray(vector<int> &arr, int low, int mid, int high){
	vector<int> retArr(3); // return array of size 3 to store max left, max right, max crossing
	int leftSum = -INT_MIN; // left subarray sum initialized to small value
	int rightSum = -INT_MIN; // right subarray sum initialized to small value
	int sum = 0; // sum temp variable initialized to 0
	int maxLeft; // variable for max of left array
	int maxRight; // max of right array
	for(int i = mid; i > low; i--){
			sum += arr[i];
			if(sum > leftSum){
				leftSum = sum;
				maxLeft = i;
			}
	}
	sum = 0; // reset sum to 0 to add up values of right array
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
/*
Obtains the final max subarray for the divide and conquer algorithm. Recursively breaks down the array into smaller subarrays and obtains a final maximum subarray by calling maxCrossingSum and returning the maximum of the left max subarray, right max subarray, and the max crossing subarray. Unlike maxSubArraySum, it returns a maximum resulting vector to the problem.
return value: (low, high, sum)
*/
vector<int> maxSubArray(vector<int> &arr, int low, int high){
	vector<int> retArr(3); // creates initial vector of size 3
	vector<int> crossArr(3); //A.K.A. retArr
	int mid;
	vector<int> leftArr(3); // initial left vector size 3
	vector<int> rightArr(3); // initial right vector size 3
	int leftSum; // sum of left max subarray
	int rightSum; // sum of right max subarray
	int crossSum; // sum of crossing max subarray
	if(high == low){ // base case: one element in the array
		crossArr[0] = low;
		crossArr[1] = high;
		crossArr[2] = arr[low];
		return crossArr;
	}
	else{
		mid = (low+high);
		mid /= 2; // find midpoint of indices
		leftArr = maxSubArray(arr, low, mid); // find max left subarray
		rightArr = maxSubArray(arr, mid + 1, high); // find max right subarray
		crossArr = maxCrossingSubArray(arr, low, mid, high); // find max crossing subarray
		leftSum = sum(leftArr); // find sum of above left array
		rightSum = sum(rightArr); // sum of above right array
		crossSum = sum(crossArr); // sum of above crossing array
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
/*
Serves as driver for the divAndConq function. Takes in two input files <inputfile>.txt and <output>.txt
It parses the input file to obtain an array of integers(stored in a vector). divAndConq() is then called, passing in this input vector, the start index 1, and its size(number of elements)
*/
int main(int argc, char * argv[]){
	vector<int> arr; // array to store interger values
	int val; // value to store the integer on each line of input file
	ifstream file(argv[1]); // input file
	while(file >> val){ // obtains integer from file
		arr.push_back(val); // pushes integer into vector
	}
	int maxSum = 0; // initialized max sum to 0
	vector<int> retArr(3); // initial vector to pass into maxSubArray()
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
