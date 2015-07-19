class Solution
{
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k)
    {
        vector<int> res;
        // This double-ended queue will keep the candidates for the sliding 
        // window maximums.
        deque<int> maxCandidateIndexes;

        for (int windowIndex = 0; windowIndex < nums.size(); windowIndex++)
        {
            // Remove the candidate which has just fallen out of the left 
            // boundary of the current sliding window.
            if ((!maxCandidateIndexes.empty()) &&
                (maxCandidateIndexes.front() == windowIndex - k))
            {
                maxCandidateIndexes.pop_front();
            }

            // nums[windowIndex] is within the current sliding window and 
            // any number less than it and before it can't be the maximum 
            // for either the current sliding window or any future sliding 
            // window as we move forward.
            while ((!maxCandidateIndexes.empty()) &&
                (nums[maxCandidateIndexes.back()] < nums[windowIndex]))
            {
                maxCandidateIndexes.pop_back();
            }

            // If maxCandidateIndexes is empty, nums[windowIndex] is the 
            // maximum of the current sliding window; otherwise, it is a 
            // candidate for the maximum of future sliding windows.
            maxCandidateIndexes.push_back(windowIndex);

            // If windowIndex < k - 1, we haven't examined the first k 
            // numbers which comprise the first sliding window.
            if (windowIndex >= k - 1)
            {
                // It can be proven by induction that the first number 
                // in maxCandidateIndexes is the maximum of the current 
                // sliding window.
                res.push_back(nums[maxCandidateIndexes.front()]);
            }
        }

        return res;
    }
};