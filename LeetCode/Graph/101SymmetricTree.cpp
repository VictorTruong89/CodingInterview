/**
 * @file 101SymmetricTree.cpp
 * @author VictorTruong
 * 
 * @brief Given the root of a binary tree. Check if it is a summetric tree around its center
 * @date 2022-07-08
 * @link https://leetcode.com/problems/symmetric-tree/ @endlink
 */

/**
 * @brief Example 1:
 * Input: root = [1,2,2,3,4,4,3]
 * Output: true
 * 
 * 
 * @brief Example 2:
 * Input: root = [1,2,2,null,3,null,3]
 * Output: false
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

/*========== Recursive Method ==========*/
class Solution {
public:
    bool symmetryChildNode(TreeNode* leftNode, TreeNode* rightNode) {
        // Check nullptr
        if(leftNode == nullptr && rightNode == nullptr)
            return true;
        else if(leftNode == nullptr || rightNode == nullptr)
            return false;
    
        if(leftNode->val != rightNode->val)
            return false;
        else
            return symmetryChildNode(leftNode->left, rightNode->right) &&
                    symmetryChildNode(leftNode->right, rightNode->left);
    }

    bool isSymmetric(TreeNode* root) {
        // Check if root is nullptr
        if(root == nullptr)
            return true;
        else 
            return symmetryChildNode(root->left, root->right);
    }
};


/*========== Breadth First Traversal ==========*/
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        // Check if root is nullptr
        if (root == nullptr)
            return true;
        
        // Add the rootPair as 1st element in BFS queue
        std::queue< std::pair<TreeNode*, TreeNode*> > q;
        q.push( std::make_pair(root->left, root->right) );

        while(!q.empty()) {
            // Dequeue the current pairNode to compare
            auto p = q.front();
            q.pop();
            TreeNode* l = p.first;
            TreeNode* r = p.second;

            // Compare 2 element of pair for symmetricity
            if (l == nullptr && r == nullptr)
                continue;
            else if (l == nullptr || r == nullptr)
                return false;
            else if (l->val != r->val)
                return false;
            
            // Add 2 more pair to BFS queue
            q.push(std::make_pair(l->left, r->right));
            q.push(std::make_pair(l->right, r->left));
        }

        return true;
    }
};


/*========== Depth First Traversal ==========*/
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        // Check if root is nullptr
        if (root == nullptr)
            return true;
        
        // Add root childNode as 1st elment in DFS stack
        std::stack< std::pair<TreeNode*, TreeNode*> > s;
        s.push(std::make_pair(root->left, root->right));

        while(!s.empty()) {
            // Pop out top element to compare
            auto p = s.top();
            s.pop();
            TreeNode* l = p.first;
            TreeNode* r = p.second;

            if (l == nullptr && r == nullptr) 
                continue;
            else if (l == nullptr || r == nullptr)
                return false;
            else if (l->val != r->val)
                return false;
            
            // Add 2 childNode left/right to DFS stack
            s.push(std::make_pair(l->left, r->right));
            s.push(std::make_pair(l->right, r->left));
        }

        return true;
    }
};
