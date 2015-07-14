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
    // Find the reverse path from p to root.
    vector<TreeNode*> findReversePathToRoot(TreeNode* root, TreeNode* p)
    {
        if (root == p)
        {
            return vector<TreeNode*>{root};
        }

        // This map keeps the parent nodes for the nodes visited 
        // during the search.
        unordered_map<TreeNode*, TreeNode*> parentMap;
        stack<TreeNode*> searchSt;
        TreeNode* curr = nullptr;

        // Use depth-first search to reach p.
        searchSt.push(root);
        while (!searchSt.empty())
        {
            curr = searchSt.top();
            searchSt.pop();

            if (curr->left != nullptr)
            {
                searchSt.push(curr->left);
                parentMap.insert(make_pair(curr->left, curr));

                // We have found p, so stop the search.
                if (curr->left == p)
                {
                    break;
                }
            }

            if (curr->right != nullptr)
            {
                searchSt.push(curr->right);
                parentMap.insert(make_pair(curr->right, curr));

                // We have found p, so stop the search.
                if (curr->right == p)
                {
                    break;
                }
            }
        }

        // Build the reverse path from p to root based on the parent 
        // node map.
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
        // Find the two reverse paths from p and q, respectively, to root.
        vector<TreeNode*> reversePathFromPToRoot = findReversePathToRoot(root, p);
        vector<TreeNode*> reversePathFromQToRoot = findReversePathToRoot(root, q);

        // Compare the TreeNodes from back to front in the two reverse paths 
        // and the last identical TreeNode is the lowest common ancestor of p and q.
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