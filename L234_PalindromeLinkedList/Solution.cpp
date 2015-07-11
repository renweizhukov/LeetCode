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
    ListNode* reverseList(ListNode* head)
    {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        
        while (curr != nullptr)
        {
            ListNode* tmp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = tmp;
        }
        
        return prev;
    }
    
public:
    bool isPalindrome(ListNode* head) 
    {
        if ((head == nullptr) || (head->next == nullptr))
        {
            return true;
        }
        
        ListNode *slow = head;
        ListNode *fast = head;
        while (fast != nullptr)
        {
            slow = slow->next;
            fast = fast->next;
            if (fast != nullptr)
            {
                fast = fast->next;
            }
        }
        
        bool res = true;
        ListNode *newHead = reverseList(slow);
        ListNode *firstHalf = head;
        ListNode *secondHalf = newHead;
        while (secondHalf != nullptr)
        {
            if (firstHalf->val != secondHalf->val)
            {
                res = false;
                break;
            }
            
            firstHalf = firstHalf->next;
            secondHalf = secondHalf->next;
        }
        
        (void)reverseList(newHead);
        
        return res;
    }
};