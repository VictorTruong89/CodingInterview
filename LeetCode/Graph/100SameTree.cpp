/**
 * @file 100SameTree.cpp
 * @author VictorTruong
 * 
 * @brief Given the roots of 2 binary-tree (p & q), check if they are identical
 * @date 2022-07-07
 * @link https://leetcode.com/problems/same-tree/ @endlink
 */

/**
 * @brief Example 1:
 * Input: p = [1,2,3], q = [1,2,3]
 * Output: true
 * 
 * 
 * @brief Example 2:
 * Input: p = [1,2], q = [1,null,2]
 * Output: false
 * 
 * 
 * @brief Example 3:
 * Input: p = [1,2,1], q = [1,1,2]
 * Output: false
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

/*========== Recursive Method ==========*/
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        // Check for nullptr 
        if(p == nullptr && q == nullptr)
            return true;
        else if(p == nullptr || q == nullptr)
            return false;
        
        // Then compare the value
        if(p->val != q->val)
            return false;
        
        // Recurse to subNode left & right
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};


/*========== Breadth First Traversal ==========*/
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        // Check for nullptr 
        if(p == nullptr && q == nullptr)
            return true;
        else if(p == nullptr || q == nullptr)
            return false;
        
        // Then compare the value
        if(p->val != q->val)
            return false;
        
        std::queue<TreeNode*> pQueue;
        pQueue.push(p);
        std::queue<TreeNode*> qQueue;
        qQueue.push(q);

        // Because this is a Tree instead of Graph, we ignore the visited Node scenario

        while(!pQueue.empty() && !qQueue.empty()) {
            // Dequeue the current Node, which is at top of std::queue
            TreeNode* pNode = pQueue.front();
            pQueue.pop();
            TreeNode* qNode = qQueue.front();
            qQueue.pop();

            // Compare the Left childNode
            if(pNode->left && qNode->left) {
                if(pNode->left->val != qNode->left->val)
                    return false;
                else {
                    pQueue.push(pNode->left);
                    qQueue.push(qNode->left);
                }
            } else if(pNode->left == nullptr && qNode->left)
                return false;
            else if(qNode->left && qNode->left == nullptr)
                return false;

            // Compare the Right childNode
            if(pNode->right && qNode->right) {
                if(pNode->right->val != qNode->right->val)
                    return false;
                else {
                    pQueue.push(pNode->right);
                    qQueue.push(qNode->right);
                }
            } else if(pNode->right == nullptr && qNode->right)
                return false;
            else if(pNode->right && qNode->right == nullptr)
                return false;
        }
        
        return true;
    }
};