class Solution
{
public:
    vector<int> productExceptSelf(vector<int>& nums)
    {
        int n = nums.size();
        vector<int> res(n, 1);

        int productBefore = nums[0];
        for (int i = 1; i < n; i++)
        {
            res[i] = productBefore;
            productBefore *= nums[i];
        }

        int productAfter = nums[n - 1];
        for (int i = n - 2; i >= 0; i--)
        {
            res[i] *= productAfter;
            productAfter *= nums[i];
        }

        return res;
    }
};