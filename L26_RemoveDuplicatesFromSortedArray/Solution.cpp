class Solution
{
public:
    int removeDuplicates(vector<int>& nums)
    {
        int n = nums.size();
        if (n < 2)
        {
            // The sorted array has less than 2 elements, 
            // so it can't have any duplicates.
            return n;
        }

        int j = 1; // the index of available slot for non-duplicates
        for (int i = 1; i < n; i++)
        {
            if (nums[i] != nums[i - 1])
            {
                if (j != i)
                {
                    // Move nums[j] to nums[i].
                    nums[j] = nums[i];
                }
                // Increase j by 1 since A[j] has been used.
                j++;
            }
            // If currValue == lastValue, we should remove currValue, 
            // so we increase i by 1 but keep j unchanged.
        }

        return j;
    }
};