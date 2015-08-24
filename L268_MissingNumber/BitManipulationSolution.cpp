class Solution
{
public:
    int missingNumber(vector<int>& nums)
    {
        // Calculate the xor value of all numbers from 0 to n.
        int xorFrom0ToN = 0;
        for (int i = 0; i <= nums.size(); i++)
        {
            xorFrom0ToN ^= i;
        }

        // The missing number will be xor of xorFrom0ToN and all numbers in nums.
        return accumulate(nums.begin(), nums.end(), xorFrom0ToN, bit_xor<int>());
    }
};