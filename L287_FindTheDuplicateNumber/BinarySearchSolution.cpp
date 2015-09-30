class Solution
{
public:
    // Use binary search (Time complexity: O(n*log(n))).
    int findDuplicate(vector<int>& nums)
    {
        int len = nums.size();
        int left = 1;
        int right = len - 1;
        int mid = 0;
        int count = 0;
        // Partition the numbers into two subarrays: LE and G 
        // where LE contains numbers <= mid and G contains 
        // numbers > mid. Note that count is the count of numbers 
        // in LE.
        while (left < right)
        {
            mid = (left + right) / 2;
            count = 0;
            for (int i = 0; i < len; i++)
            {
                if (nums[i] <= mid)
                {
                    count++;
                }
            }

            // If LE has more than mid numbers, then the duplicate 
            // is within [left, mid]; otherwise it is within 
            // [mid + 1, right].
            if (count > mid)
            {
                right = mid;
            }
            else
            {
                left = mid + 1;
            }
        }

        return left;
    }
};