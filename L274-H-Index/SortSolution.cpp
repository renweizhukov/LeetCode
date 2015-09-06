class Solution
{
public:
    int hIndex(vector<int>& citations)
    {
        // Sort the citations in a non-decreasing order.
        sort(citations.begin(), citations.end());

        // The maximum hIndex is (n - the minimum citation index i)
        // such that citations[i] >= n - i.
        int n = citations.size();
        for (int i = 0; i < n; i++)
        {
            if (citations[i] >= n - i)
            {
                return (n - i);
            }
        }

        // No such i exists, so the maximum hIndex is 0.
        return 0;
    }
};