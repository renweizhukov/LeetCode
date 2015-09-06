class Solution
{
public:
    int hIndex(vector<int>& citations)
    {
        int n = citations.size();
        // The key of this map is the number of citations per paper, 
        // and the value of this map is the count of papers which 
        // have the number of citations. Note that the range of the 
        // maximum hIndex is [0, n].
        vector<int> citationToCntPaperMap(n + 1);

        // Update the above map.
        for (auto &c : citations)
        {
            if (c <= n)
            {
                citationToCntPaperMap[c]++;
            }
            else
            {
                // If the number of citations for one paper is greater 
                // than n, it can be replaced by n and it won't affect 
                // the result of the maximum hIndex.
                citationToCntPaperMap[n]++;
            }
        }

        // accumulatedCntPaper = the accumulated count of papers with 
        // the citation numbers from n to i.
        int accumulatedCntPaper = 0;
        for (int i = n; i >= 0; i--)
        {
            accumulatedCntPaper += citationToCntPaperMap[i];
            if (accumulatedCntPaper >= i)
            {
                return i;
            }
        }

        // Since accumulatedCntPaper[n,...,0] >= 0, we should have already 
        // returned within the above for loop when i = 0. The return here 
        // is added for the code completeness.
        return 0;
    }
};