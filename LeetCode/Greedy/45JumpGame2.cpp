/**
 * @file 45JumpGame2.cpp
 * @author VictorTruong
 * 
 * @brief 
 * @date 2022-07-12
 * @link https://leetcode.com/problems/jump-game-ii/ @endlink
 * 
 * 
 * Given an array of non-negative integers nums, you are initially positioned at the first index of the array.
 * Each element in the array represents your maximum jump length at that position.
 * Your goal is to reach the last index in the minimum number of jumps.
 * You can assume that you can always reach the last index.
 * 
 * Constraints:
 *      1 <= nums.length <= 10^4
 *      0 <= nums[i] <= 1000
 */

/**
 * @brief Example 1:
 * Input: nums = [2,3,1,1,4]
 * Output: 2
 * Explanation: The minimum number of jumps to reach the last index is 2. Jump 1 step from index 0 to 1, then 3 steps to the last index.
 * 
 * 
 * @brief Example 2:
 * Input: nums = [2,3,0,1,4]
 * Output: 2
 */


/**
 * @brief Solution explanation
 * @link https://iq.opengenus.org/jump-game-ii/ @endlink
 */
class Solution {
public:
    bool canJump(vector<int>& nums) {
        // Left & right pointer to point to the start & end of a segment
        // A segment refers to a step a particular index can move
        int left = 0;
        int right = 0;
        int jumps = 0;

        // While right pointer not reach the end of the vector<int> nums
        while(right < nums.size() - 1) {
            // Loop through the segment and maximize the reach
            int maxReach = 0;
            for(int i = left; i < right + 1; i++)
                maxReach = max(maxReach, nums[i] + i);
            
            // Update the pointers (left -> right + 1) and (right -> maximum reach)
            left = right + 1;
            right = maxReach;

            // Count the number of jumps
            jumps++;
        }

        // loop terminates when right-pointer reach the end
        return jumps;
    }
};