/**
 * @file 145BinaryTreePostorderTraversal.cpp
 * @author VictorTruong
 * 
 * @brief Given the root of a binary tree, return the postorder traversal of its nodes' values.
 * @date 2022-07-15
 * @link https://leetcode.com/problems/binary-tree-postorder-traversal/ @endlink
 */

/**
 * @brief Example 1:
 * Input: root = [1,null,2,3]
 * Output: [3,2,1]
 * 
 * 
 * @brief Example 2:
 * Input: root = []
 * Output: []
 * 
 * 
 * @brief Example 3:
 * Input: root = [1]
 * Output: [1]
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        std::vector<int> ret;
        dfsReverse(root, ret);
        return ret;
    }
    
    void dfsReverse(TreeNode* root, vector<int>& ans) {
        if(root == nullptr)
            return;
        else {
            dfsReverse(root->left, ans);
            dfsReverse(root->right, ans);
            ans.push_back(root->val);
        }
    }
};