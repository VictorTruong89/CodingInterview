/**
 * @file 102BinaryTreeLevelOrderTraversal.cpp
 * @author VictorTruong
 * 
 * @brief Given the root of a binary tree. Return the level order travel of its nodes' values (i.e., from left to right, level by level).
 * @date 2022-07-08
 * @link https://leetcode.com/problems/binary-tree-level-order-traversal/ @endlink
 * 
 */

/**
 * @brief Example 1:
 * Input: root = [3,9,20,null,null,15,7]
 * Output: [[3],[9,20],[15,7]]
 * 
 * 
 * @brief Example 2:
 * Input: root = [1]
 * Output: [[1]]
 * 
 * 
 * @brief Example 3:
 * Input: root = []
 * Output: []
 */


/**
 * Definition for a binary tree node.
 */ 
 struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


/*========== Level Order Traversal Method ==========*/
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        std::vector< std::vector<int> > ret {};
        
        // Check nullptr root
        if (root == nullptr) 
            return ret;

        // Different from normal BFS, this queue contains Node of a same level only
        std::queue<TreeNode*> q;
        q.push(root);

        while(!q.empty()) {
            // Count the number of Nodes in a same level
            int countNode = q.size();
            std::vector<int> levelValue {};

            for (int i=0; i < countNode; i++) {
                TreeNode* currNode = q.front();
                q.pop();

                // Here not require to check nullptr because only non-NULL node is added to queue
                levelValue.push_back(currNode->val);

                // Add next-level Nodes to queue
                if (currNode->left) q.push(currNode->left);
                if (currNode->right) q.push(currNode->right);
            }

            ret.push_back(levelValue);
        }

        return ret;
    }
};