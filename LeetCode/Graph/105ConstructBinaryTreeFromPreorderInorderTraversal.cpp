/**
 * @file 105ConstructBinaryTreeFromPreorderInorderTraversal.cpp
 * @author VictorTruong
 * 
 * @brief Construct Binary Tree from Preorder and Inorder Traversal
 * @date 2022-07-14
 * @link https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/ @endlink
 * 
 * 
 * Given 2 integer arrays preorder and inorder where preorder is the preorder traversal of a binary tree 
 * and inorder is the inorder traversal of the same tree, construct and return the binary tree.
 * 
 * Constraints:
 *      1 <= preorder.length <= 3000
 *      inorder.length == preorder.length
 *      -3000 <= preorder[i], inorder[i] <= 3000
 *      preorder and inorder consist of unique values.
 *      Each value of inorder also appears in preorder.
 *      preorder is guaranteed to be the preorder traversal of the tree.
 *      inorder is guaranteed to be the inorder traversal of the tree.
 */

/**
 * @brief Example 1:
 * Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
 * Output: [3,9,20,null,null,15,7]
 * 
 * 
 * @brief Example 2:
 * Input: preorder = [-1], inorder = [-1]
 * Output: [-1]
 */

/**
 * @brief Algorithm explanation
 * @link https://www.geeksforgeeks.org/construct-tree-from-given-inorder-and-preorder-traversal/ @endlink
 * 
 * @brief Method #3
 * 1st element in PreOrder is root
 * 1st element in InOrder is left-most Node
 * Create a Stack to store the visited path while traversing PreOrder array
 * Create a Set to maintain the Node in which the next right subtree is expected
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
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = preorder.size();

        // This set to store Node that should be LeftNode
        std::set<TreeNode*> leftNode;

        // This stack to store visited Node in PreOrder
        std::stack<TreeNode*> visitedPreorder;
        
        TreeNode* root = nullptr;

        for(int pre = 0, in = 0 ; pre < n; ) {
            TreeNode* node = nullptr;
            do {
                node = new TreeNode(preorder[pre]);

                // 1st element of PreOrder array is the Root
                // Initialze here, instead of outside, to easily push it to stack Visited
                if(root == nullptr)
                    root = node;
                
                // 
                if(visitedPreorder.size() > 0) {
                    if( leftNode.find(visitedPreorder.top()) != leftNode.end() ) {
                        leftNode.erase( visitedPreorder.top() );
                        visitedPreorder.top()->right = node;
                        visitedPreorder.pop();
                    } else {
                        visitedPreorder.top()->left = node;
                    }
                }

                // Push the newly created Node to stack visitedPreorder
                visitedPreorder.push(node);

            } while( (preorder[pre++] != inorder[in]) && (pre < n) );

            node = nullptr;
            while(visitedPreorder.size() > 0 && in < n && visitedPreorder.top()->val == inorder[in]) {
                node = visitedPreorder.top();
                visitedPreorder.pop();
                in++;
            }

            if(node != nullptr) {
                leftNode.insert(node);
                visitedPreorder.push(node);
            }
        }

        return root;
    }
};