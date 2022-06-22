/**
 * @file LinkedListRemoveNode.cpp
 * @author VictorTruong
 * 
 * @brief Remove Nth Node From End of List
 * @date 2022-06-21
 * @link https://leetcode.com/problems/remove-nth-node-from-end-of-list/
 * 
 * Given the head of a linked list, remove the nth node from the end of the list and return its head.
 * 
 * Constraints:
 * The number of nodes in the list is sz.
 * 1 <= sz <= 30
 * 0 <= Node.val <= 100
 * 1 <= n <= sz
 */

/**
 * @brief Example 1:
 * Input: head = [1,2,3,4,5], n = 2
 * Output: [1,2,3,5]
 * 
 * @brief Example 2:
 * Input: head = [1], n = 1
 * Output: []
 * 
 * @brief Example 3:
 * Input: head = [1,2], n = 1
 * Output: [1]
 */

/**
 * Definition for singly-linked list.
 */ 
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // The solution is to maintain 2 Nodes
        // 1st Node traverse til the end of Linked List
        // 2nd Node keeps a distance of n-Node from the 1st Node
        // When 1st Node reach the end, remove the 2nd Node.
        // To support the Node removal, create 3rd Node immediately before 2nd Node
        
        // 1st Node starts at head
        ListNode* curNode = head; 
        // 2nd Node as explained
        ListNode* delNode; 
        // 3rd Node as explained
        ListNode* prevNode;
        
        int distance = 0;
        int listLength = 0;  // In case n == LinkedList length
        bool delNodeStart = false;
        
        // Check the case LinkedList has only 1 Node
        if(head->next == nullptr)
            return nullptr;
        
        while(curNode != nullptr) {
            // Traverse the curNode to the end of LinkedList
            curNode = curNode->next;
            listLength++;
            
            // distance should increase until it reaches "n"
            if(distance < n)
                distance++;
            
            // When (distance == n) delNode traverses together with curNode
            if(distance == n) {
                if(!delNodeStart)
                    delNode = head;
                else
                    delNode = delNode->next;
                
                // Update delNodeStart only after delNode starts at head
                delNodeStart = true;
            }
            
            // When delNode passes headNode, preNode start to move
            if(delNode == head->next)
                prevNode = head;
            else if((delNode != head) && (delNode != nullptr))
                prevNode = prevNode->next;

        }

        // If listLength == n >> Delete the headNode
        if(listLength == n)
            return head->next;
        
        // When curNode reaches end >> Let's delete the delNode
        if(n == 1) {
            // delNode is the same as endNode
            prevNode->next = nullptr;
        } else {
            prevNode->next = delNode->next;
        }
        
        return head;
    }
};