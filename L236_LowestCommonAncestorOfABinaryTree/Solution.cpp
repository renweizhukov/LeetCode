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
    vector<TreeNode*> findReversePathToRoot(TreeNode* root, TreeNode* p)
    {
        if (root == p)
        {
            return vector<TreeNode*>{root};
        }

        unordered_map<TreeNode*, TreeNode*> parentMap;
        stack<TreeNode*> searchSt;
        TreeNode* curr = nullptr;

        searchSt.push(root);
        while (!searchSt.empty())
        {
            curr = searchSt.top();
            searchSt.pop();

            if (curr->left != nullptr)
            {
                searchSt.push(curr->left);
                parentMap.insert(make_pair(curr->left, curr));

                if (curr->left == p)
                {
                    break;
                }
            }

            if (curr->right != nullptr)
            {
                searchSt.push(curr->right);
                parentMap.insert(make_pair(curr->right, curr));

                if (curr->right == p)
                {
                    break;
                }
            }
        }

        vector<TreeNode*> path{ p };
        curr = parentMap[p];
        while (curr != root)
        {
            path.push_back(curr);
            curr = parentMap[curr];
        }

        path.push_back(root);

        return path;
    }

public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        vector<TreeNode*> reversePathFromPToRoot = findReversePathToRoot(root, p);
        vector<TreeNode*> reversePathFromQToRoot = findReversePathToRoot(root, q);

        int ip = reversePathFromPToRoot.size() - 1;
        int iq = reversePathFromQToRoot.size() - 1;
        for (; (ip >= 0) && (iq >= 0); ip--, iq--)
        {
            if (reversePathFromPToRoot[ip] != reversePathFromQToRoot[iq])
            {
                break;
            }
        }

        return reversePathFromPToRoot[ip + 1];
    }
};