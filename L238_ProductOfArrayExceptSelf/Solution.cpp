class Solution
{
public:
    vector<int> productExceptSelf(vector<int>& nums)
    {
        int n = nums.size();
        vector<int> res(n, 1);

        // For each nums[i], calculate the product of elements 
        // before i.
        int productBefore = nums[0];
        for (int i = 1; i < n; i++)
        {
            res[i] = productBefore;
            productBefore *= nums[i];
        }

        // For each nums[i], calculate the product of elements 
        // after i, multiple it by the product of elements 
        // before i, and obtain the product of the array except 
        // nums[i].
        int productAfter = nums[n - 1];
        for (int i = n - 2; i >= 0; i--)
        {
            res[i] *= productAfter;
            productAfter *= nums[i];
        }

        return res;
    }
};