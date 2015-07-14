/**
* Definition for singly-linked list.
* struct ListNode {
*     int val;
*     ListNode *next;
*     ListNode(int x) : val(x), next(NULL) {}
* };
*/
class Solution
{
public:
    void deleteNode(ListNode* node)
    {
        // Since node is not the tail node, node->next 
        // must not be NULL. We can't modify the previous  
        // link to the current node, so we have to convert 
        // the current node into next node by updating its 
        // node value and then delete next node.
        node->val = node->next->val;
        ListNode *tmp = node->next;
        node->next = tmp->next;
        delete tmp;
    }
};