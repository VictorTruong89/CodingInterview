/**
 * @file 94BinaryTreeInorderTraversal.cpp
 * @author VictorTruong
 * 
 * @brief Given the root of a binary tree, return the inorder traversal of its nodes' values.
 * @date 2022-07-15
 * @link https://leetcode.com/problems/binary-tree-inorder-traversal/
 */

/**
 * @brief Example 1:
 * Input: root = [1,null,2,3]
 * Output: [1,3,2]
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
    vector<int> inorderTraversal(TreeNode* root) {
        std::vector<int> ret {};
        dfs(root, ret);
        return ret;
    }
    
    void dfs(TreeNode* root, std::vector<int>& ans) {
        if(root == nullptr)
            return;
        else {
            dfs(root->left, ans);
            ans.push_back(root->val);
            dfs(root->right, ans);
        }
    }
};