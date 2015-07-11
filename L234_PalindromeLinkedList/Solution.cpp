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
    // Reverse a list.
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
        
        // Use two pointers to find the middle node. 
        // The slow pointer will move forward by one step 
        // each time while the fast pointer will move 
        // forward by two steps each time if possible.
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
        // Split the list into two sublists where "slow" 
        // is the head of the second sublist. Then reverse 
        // the second sublist. Note that 
        // (1) we don't need to disconnect the tail node of
        // the first sublist with "slow";
        // (2) if the total number of ListNodes is odd, the 
        // first sublist contains one more ListNode than the 
        // second sublist.
        ListNode *newHead = reverseList(slow);
        
        // Compare the ListNodes in the two sublists.
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
        
        // Reverse the second sublist to restore the list.
        (void)reverseList(newHead);
        
        return res;
    }
};