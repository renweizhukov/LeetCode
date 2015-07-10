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
        int currIndex = 0;
        stack<TreeNode*> stNode;

        TreeNode *currNode = root;
        while ((currNode != nullptr) || (!stNode.empty()))
        {
            if (currNode != nullptr)
            {
                stNode.push(currNode);
                currNode = currNode->left;
            }
            else
            {
                currNode = stNode.top();
                currIndex++;
                if (currIndex == k)
                {
                    break;
                }

                stNode.pop();
                currNode = currNode->right;
            }
        }

        return currNode->val;
    }
};