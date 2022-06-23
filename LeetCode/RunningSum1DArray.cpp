/**
 * @file RunningSum1DArray.cpp
 * @author VictorTruong
 * 
 * @brief Given an array nums. We define a running sum of an array as runningSum[i] = sum(nums[0]…nums[i]).
 * @date 2022-06-23
 * @link https://leetcode.com/problems/running-sum-of-1d-array/ @endlink
 * 
 * Constraints:
 * 1 <= nums.length <= 1000
 * -10^6 <= nums[i] <= 10^6
 */

/**
 * @brief Example 1:
 * Input: nums = [1,2,3,4]
 * Output: [1,3,6,10]
 * Explanation: Running sum is obtained as follows: [1, 1+2, 1+2+3, 1+2+3+4].
 * 
 * 
 * @brief Example 2:
 * Input: nums = [1,1,1,1,1]
 * Output: [1,2,3,4,5]
 * Explanation: Running sum is obtained as follows: [1, 1+1, 1+1+1, 1+1+1+1, 1+1+1+1+1].
 * 
 * @brief Example 3:
 * Input: nums = [3,1,2,10,1]
 * Output: [3,4,6,16,17]
 */

class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
        int sum = 0;
        
        vector<int> runSum {};
        
        for(int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            runSum.push_back(sum);
        }
        
        return runSum;
    }
};
