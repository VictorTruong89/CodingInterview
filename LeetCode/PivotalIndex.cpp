/**
 * @file PivotalIndex.cpp
 * @author VictorTruong
 * 
 * @brief Given an array of integers, calculate the pivot index of this array.
 * @date 2022-06-23
 * @link https://leetcode.com/problems/find-pivot-index/ @endlink
 * 
 * The pivot index is the index where the sum of all the numbers 
 * strictly to the left of the index is equal to the sum of 
 * all the numbers strictly to the index's right.
 * 
 * If the index is on the left edge of the array, then 
 * the left sum is 0 because there are no elements to the left. 
 * This also applies to the right edge of the array.
 * 
 * Return the leftmost pivot index. If no such index exists, return -1.
 */

/**
 * @brief Example 1:
 * Input: nums = [1,7,3,6,5,6]
 * Output: 3
 * Explanation: Left sum = nums[0] + nums[1] + nums[2] = 11 Right sum = nums[4] + nums[5] = 11
 * 
 * 
 * @brief Example 2:
 * Input: nums = [1,2,3]
 * Output: -1
 * Explanation: There is no index that satisfies the conditions in the problem statement.
 * 
 * 
 * @brief Example 3:
 * Input: nums = [2,1,-1]
 * Output: 0
 * Explanation: Left sum = 0 (no elements to the left of index 0) Right sum = nums[1] + nums[2] = 0
 */

class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        
        // Special case
        if(nums.size() == 1) {
            if(nums[0] != 0) return -1;
            else return 0;
        }
        
        // At pivotal idex, sumTotal == (sumLeft + pivot/2)
        float sumLeft  = 0;
        float sumTotal = 0;
        vector<float> sums;
        
        for(int i = 0; i < nums.size(); i++) {
            // Step 1: Traverse pivot & Calculate sumLeft
            sumLeft = sumTotal + static_cast<float>(nums[i]) / 2;
            
            // Step 2: Save sumLeft to search later
            sums.push_back(sumLeft);
            
            // Step 3: Find total sum
            sumTotal += nums[i];
        }
        
        // Step 4: Search if any sumLeft == sumTotal / 2
        auto iterator = std::find(sums.begin(), sums.end(), (sumTotal / 2) );
        if(iterator == sums.end()) 
            return -1;
        else 
            return static_cast<int>(iterator - sums.begin());
    }
};
