class Solution
{
public:
    // Use the "Two Pointers" approach (i.e., the Floyd's 
    // algorithm). A rigorous analysis of this problem can 
    // be found at http://keithschwarz.com/interesting/code/?dir=find-duplicate.
    // Time complexity O(n).
    int findDuplicate(vector<int>& nums)
    {
        // For each index i = 0,...,n, define a function 
        // f from nums such that f(i) = nums[i] - 1. Since 
        // the range of nums is [1, n], the range of f(i)
        // is [0, n - 1]. If we start from n, we won't be 
        // able to go back to n by keeping applying f.
        int n = nums.size() - 1;

        // slow moves one step each time while fase moves 
        // two steps each time. They will meet somewhere 
        // in the cycle.
        int slow = n;
        int fast = n;
        do
        {
            slow = nums[slow] - 1;
            fast = nums[nums[fast] - 1] - 1;
        } while (slow != fast);

        // duplicate starts from n and moves one step each 
        // time. If slow continues moving one step each 
        // time, slow and duplicate will meet at the beginning 
        // of the cycle.
        int duplicate = n;
        while (duplicate != slow)
        {
            duplicate = nums[duplicate] - 1;
            slow = nums[slow] - 1;
        }

        return duplicate + 1;
    }
};