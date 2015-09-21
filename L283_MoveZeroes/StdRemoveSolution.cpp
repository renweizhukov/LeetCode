class Solution
{
public:
    void moveZeroes(vector<int>& nums)
    {
        // std::remove will move the non-zero numbers to the front 
        // while maintaining their relative order, and it will return 
        // the iterator right after the last non-zero element.
        auto itZeroStart = remove(nums.begin(), nums.end(), 0);

        // Set the trailing numbers after itZeroStart 
        // (including itZeroStart) to zero.
        for (auto it = itZeroStart; it != nums.end(); it++)
        {
            *it = 0;
        }
    }
};