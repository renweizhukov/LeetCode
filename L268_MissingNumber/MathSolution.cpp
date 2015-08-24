class Solution
{
public:
    int missingNumber(vector<int>& nums)
    {
        // sumOf0ToN = the sum of numbers from 0 to n.
        // sumOfNums = the sum of numbers in nums.
        // We define long here to handle the int overflow case.
        long sumOf0ToN = (nums.size() + 1)*nums.size() / 2;
        long sumOfNums = accumulate(nums.begin(), nums.end(), 0);

        return sumOf0ToN - sumOfNums;
    }
};