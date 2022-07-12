/**
 * @file 55JumpGame.cpp
 * @author VictorTruong
 * 
 * @brief 
 * @date 2022-07-12
 * @link https://leetcode.com/problems/jump-game/ @endlink
 * 
 * 
 * Given an integer array nums. You are initially positioned at the array's first index, 
 * and each element in the array represents your maximum jump length at that position.
 * Return true if you can reach the last index, or false otherwise.
 * 
 * Constraints
 *      1 <= nums.length <= 10^4
 *      0 <= nums[i] <= 10^5
 */

/**
 * @brief Example 1:
 * Input: nums = [2,3,1,1,4]
 * Output: true
 * Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.
 * 
 * 
 * @brief Example 2:
 * Input: nums = [3,2,1,0,4]
 * Output: false
 * Explanation: You will always arrive at index 3 no matter what. Its maximum jump length is 0, which makes it impossible to reach the last index.
 */

class Solution {
public:
    bool canJump(vector<int>& nums) {
        // Start from the last index
        int curr = nums.size() - 1;
        
        for(int i = curr; i >= 0; i--) {
            if(i + nums[i] >= curr)
                curr = i;
        }
        
        if(curr == 0)
            return true;
        else
            return false;
    }
};