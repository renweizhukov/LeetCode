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
    vector<string> binaryTreePaths(TreeNode* root)
    {
        vector<string> paths;
        // If root is NULL, return an empty path vector.
        if (root == nullptr)
        {
            return paths;
        }

        // Get the path vector starting from the left child.
        vector<string> leftPaths = binaryTreePaths(root->left);
        // Concatenate root with the left paths to generate 
        // the paths starting from root.
        for (auto& lp : leftPaths)
        {
            paths.push_back(to_string(root->val) + "->" + lp);
        }

        // Get the path vector starting from the right child.
        vector<string> rightPaths = binaryTreePaths(root->right);
        // Concatenate root with the right paths to generate 
        // the paths starting from root.
        for (auto& rp : rightPaths)
        {
            paths.push_back(to_string(root->val) + "->" + rp);
        }

        // In case that both leftPaths and rightPaths are empty, 
        // i.e., root is a leaf, root itself is a path.
        if (paths.empty())
        {
            paths.push_back(to_string(root->val));
        }

        return paths;
    }
};