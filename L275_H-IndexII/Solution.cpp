class Solution
{
public:
    int hIndex(vector<int>& citations)
    {
        int n = citations.size();
        // If the vector is empty, return 0 immediately.
        if (n == 0)
        {
            return 0;
        }

        // The range of the maximum hIndex is [0, n]. Except for the 
        // case that h = 0 or n, maxHIndex = h is equivalent to 
        // (1) citations[n - h] >= h; 
        // and (2) citations[n - (h + 1)] < h + 1.

        // Consider two special cases: h is n or 0.
        if (citations[0] >= n)
        {
            // h is n.
            return n;
        }
        if (citations[n - 1] < 1)
        {
            // h is 0.
            return 0;
        }

        // If the maximum hIndex is neither n nor 0, then use the binary 
        // search to find the maximum hIndex. Given a citation index i 
        // (0 <= i <= n - 1), the corresponding "hIndex" is (n - i). 
        // 1. Since the maximum hIndex is not n, the citation index 0 
        // doesn't correspond to an hIndex.
        // 2. Since the maximum hIndex is not 0, the citation index n - 1
        // corresponds to an hIndex but may not be the maximum hIndex.
        // 3. The binary search will end when the distance between two 
        // indexes is 1, i.e., the conditions (1) and (2) are met.
        int citationIndexToNoHIndex = 0;
        int citationIndexToHIndex = n - 1;
        while (citationIndexToHIndex - citationIndexToNoHIndex > 1)
        {
            int mid = (citationIndexToNoHIndex + citationIndexToHIndex) / 2;
            if (citations[mid] < n - mid)
            {
                // mid doesn't correspond to an hIndex.
                citationIndexToNoHIndex = mid;
            }
            else
            {
                // mid corresponds to an hIndex.
                citationIndexToHIndex = mid;
            }
        }

        return n - citationIndexToHIndex;
    }
};