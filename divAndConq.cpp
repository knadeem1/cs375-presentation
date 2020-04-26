#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <numeric>//#include <bits/stdc++.h>
#include <cstdlib>
#include <cmath>
#include <climits>
#include <limits>
// Divide and Conquer implementation of max subarray problem

using namespace std;

int max(int a, int b){ return (a>b)? a:b};

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
	int leftSum = -INT_MIN;
	int rightSum = -INT_MIN;
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
		cout << "sums left, right, cross: " << leftSum << ", " << rightSum << ", "
		<< crossSum << endl;
		if(leftSum >= rightSum && leftSum >= crossSum){
			/*retArr[0] = leftArr[0];
			retArr[1] = leftArr[1];
			retArr[2] = leftArr[2];*/
			//retArr = leftArr;
			cout << "roast chicken" << endl;
			cout << "left index: " << leftArr[0] << endl;
			return leftArr;//return retArr;
		}
		else if(rightSum >= leftSum && rightSum >= crossSum){
			/*retArr[0] = rightArr[0];
			retArr[1] = rightArr[1];
			retArr[2] = rightArr[2];*/
			//retArr = rightArr;
			cout << "right index: " << rightArr[0] << endl;
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

int maxCrossingSum(vector<int> arr, int l, int m, int h) 
{ 
    // Include elements on left of mid. 
    int sum = 0; 
    int left_sum = INT_MIN; 
    for (int i = m; i >= l; i--) 
    { 
        sum = sum + arr[i]; 
        if (sum > left_sum) 
          left_sum = sum; 
    } 
  
    // Include elements on right of mid 
    sum = 0; 
    int right_sum = INT_MIN; 
    for (int i = m+1; i <= h; i++) 
    { 
        sum = sum + arr[i]; 
        if (sum > right_sum) 
          right_sum = sum; 
    } 
	return max(maxSubArraySum(arr, l, m), 
              maxSubArraySum(arr, m+1, h), 
              maxCrossingSum(arr, l, m, h));
/*  
	if(leftSum >= rightSum && leftSum >= crossSum){
			return maxCrossingSum(arr, l, m);//return retArr;
		}
		else if(rightSum > leftSum && rightSum > crossSum){
			return maxCrossingSum(arr, m+1, h);//return retArr;
		}
		else{
			return maxCrossingSum(arr, l, m, h);//return retArr;
		}
	}
*/
    // Return sum of elements on left and right of mid 
    // returning only left_sum + right_sum will fail for [-2, 1] 
    return max(left_sum + right_sum, left_sum, right_sum); 
} 
int maxSubArraySum(vector<int> arr, int low, int high){
	if(low == high) return arr[low];
	int mid = (low+high)/2;
	//return std::max({maxSubArraySum(arr, low, mid),
	//			maxSubArraySum(arr, mid + 1, high),
	//			maxCrossingSum(arr, low, mid, high)});
}

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
	int maxSum = 0;
	vector<int> retArr(3);
	int n = sizeof(arr)/sizeof(arr[0]);
	retArr = maxSubArray(arr, 0, n-1); // retArr.size() is n
	cout << "maxSum?????: " << maxSubArraySum(arr, 0, n -1) << endl;
	cout << retArr[0] << endl;
	cout << retArr[1] << endl;
	cout << retArr[2] << endl;
	return 0;
}
