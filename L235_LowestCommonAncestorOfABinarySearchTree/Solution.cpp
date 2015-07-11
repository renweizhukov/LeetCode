/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution 
{
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) 
    {
        TreeNode *curr = root;
        while (curr != nullptr)
        {
            if ((curr == p) || (curr == q))
            {
                // The lowest common ancestor is either p or q.
                return curr;
            }
            else if ((p->val <= curr->val) && (q->val <= curr->val))
            {
                // Both p and q are in the left subtree.
                curr = curr->left;
            }
            else if ((p->val > curr->val) && (q->val > curr->val))
            {
                // Both p and q are in the right subtree.
                curr = curr->right;
            }
            else
            {
                // p and q are in different subtrees, so curr is the 
                // lowest common ancestor.
                return curr;
            }
        }
        
        return nullptr;
    }
};