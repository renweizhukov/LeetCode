class Solution
{
public:
    void moveZeroes(vector<int>& nums)
    {
        // insertIndex is the index of the non-zero number which 
        // will be inserted.
        int n = nums.size();
        int insertIndex = 0;
        // enumIndex is the index of the number which is being 
        // enumerated.
        for (int enumIndex = 0; enumIndex < n; enumIndex++)
        {
            // Skip the number zero.
            if (nums[enumIndex] != 0)
            {
                // Insert the non-zero number to insertIndex 
                // if needed.
                if (insertIndex != enumIndex)
                {
                    nums[insertIndex] = nums[enumIndex];
                }
                insertIndex++;
            }
        }

        // Set the trailing numbers after insertIndex 
        // (including insertIndex) to 0.
        for (int enumIndex = insertIndex; enumIndex < n; enumIndex++)
        {
            nums[enumIndex] = 0;
        }
    }
};