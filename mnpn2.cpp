#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

bool canDivideIntoKSegmentsWithSameMex(const vector<int>& nums, int k) {
    unordered_set<int> numSet(nums.begin(), nums.end());

    // Find the Mex (smallest non-negative integer not present in the array)
    int mex = 0;
    while (numSet.count(mex)) {
        mex++;
    }

    // If Mex is greater than k - 1, it's not possible to divide into k segments with the same Mex
    if (mex > k - 1) return false;

    // If there are fewer than k occurrences of the Mex, it's not possible
    if (nums.size() < k) return false;

    return true;
}

int main() {
    // Example usage
    vector<int> nums = {0,1,7,1,0,1,0,3}; // Example array
    int k = 2; // Number of segments

    if (canDivideIntoKSegmentsWithSameMex(nums, k)) {
        cout << "It's possible to divide the array into " << k << " segments with the same Mex." << endl;
    } else {
        cout << "It's not possible to divide the array into " << k << " segments with the same Mex." << endl;
    }

    return 0;
}
