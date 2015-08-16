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
    // Generate the path string from the TreeNode val vector.
    string GetPathStringFromNums(vector<int> &pathVal)
    {
        int n = pathVal.size();
        string res;
        // For the nodes except the last node, we need to 
        // append "->" to the node values.
        for (int i = 0; i < n - 1; i++)
        {
            res += (to_string(pathVal[i]) + "->");
        }

        if (n > 0)
        {
            res += to_string(pathVal[n - 1]);
        }

        return res;
    }

public:
    vector<string> binaryTreePaths(TreeNode* root)
    {
        vector<string> paths;
        // If root is NULL, return an empty path vector immediately.
        if (root == nullptr)
        {
            return paths;
        }

        // pathVal is a vector of TreeNode values along a path 
        // starting from root.
        vector<int> pathVal({ root->val });

        // st is the stack used for the depth-first search.
        stack<TreeNode*> st;
        st.push(root);

        // visitedNodes keeps all the nodes which have been visited 
        // during the depth-first search. In other words, it keeps 
        // all the nodes which have ever been pushed into the stack.
        unordered_set<TreeNode*> visitedNodes({ root });

        // Do the depth-first search until the stack is empty.
        while (!st.empty())
        {
            TreeNode *curr = st.top();

            if ((curr->left == nullptr) && (curr->right == nullptr))
            {
                // curr is a leaf, so the current path is a path from 
                // root to a leaf and add it to paths.
                paths.push_back(GetPathStringFromNums(pathVal));

                // Remove the leaf node from pathVal which will end at 
                // the parent node of curr.
                pathVal.pop_back();

                st.pop();
            }
            else
            {
                // curr is not leaf, so we need to go down at least one 
                // level.

                // First we try pushing the left child if it hasn't 
                // been visited.
                if (curr->left != nullptr)
                {
                    auto itLeft = visitedNodes.find(curr->left);
                    if (itLeft == visitedNodes.end())
                    {
                        st.push(curr->left);
                        pathVal.push_back(curr->left->val);

                        visitedNodes.insert(curr->left);
                        continue;
                    }
                }

                // We reach here because either the left child doesn't 
                // exist or the left child has been visited. Then we try 
                // pushing the right child if it hasn't been visited.
                if (curr->right != nullptr)
                {
                    auto itRight = visitedNodes.find(curr->right);
                    if (itRight == visitedNodes.end())
                    {
                        st.push(curr->right);
                        pathVal.push_back(curr->right->val);

                        visitedNodes.insert(curr->right);
                        continue;
                    }
                }

                // The nodes in the subtree below curr have all been 
                // visited, so remove curr from pathVal which will end 
                // at the parent node of curr.
                pathVal.pop_back();
                st.pop();
            }
        }

        return paths;
    }
};