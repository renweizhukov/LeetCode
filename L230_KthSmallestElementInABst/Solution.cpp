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
    int kthSmallest(TreeNode* root, int k)
    {
        // The index of the node currently output during the 
        // inorder traversal which starts from 1.
        int currIndex = 0;
        // The TreeNode stack used in the inorder traversal.
        stack<TreeNode*> stNode;
        TreeNode *currNode = root;

        // The inorder traversal ends when st is empty and curr is NULL.
        while ((currNode != nullptr) || (!stNode.empty()))
        {
            if (currNode != nullptr)
            {
                // We go left as deep as possible.
                stNode.push(currNode);
                currNode = currNode->left;
            }
            else
            {
                // Output the top node of st.
                currNode = stNode.top();
                currIndex++;
                if (currIndex == k)
                {
                    break;
                }

                // Start processing the right subtree.
                stNode.pop();
                currNode = currNode->right;
            }
        }

        return currNode->val;
    }
};