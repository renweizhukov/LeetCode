class Solution
{
public:
    vector<int> majorityElement(vector<int>& nums)
    {
        vector<int> res;
        // Since there may be at most 2 majority elements which 
        // appear more than n/3 times, we only need to create 
        // 2 candidates. Note that the two candidates don't have 
        // to be initialized to the same value.
        int firstCandidate = 0;
        int cntFirstCandidate = 0;
        int secondCandidate = 0;
        int cntSecondCandidate = 0;

        // Below is a generalization of Boyer-Moore Majority Vote algorithm.
        // https://en.wikipedia.org/wiki/Boyer-Moore_Majority_Vote_Algorithm
        // http://gregable.com/2013/10/majority-vote-algorithm-find-majority.html
        for (auto& i : nums)
        {
            if (i == firstCandidate)
            {
                // See an occurrence of firstCandidate. 
                cntFirstCandidate++;
            }
            else if (i == secondCandidate)
            {
                // See an occurrence of secondCandidate.
                cntSecondCandidate++;
            }
            else if (cntFirstCandidate == 0)
            {
                // Since the occurrence count of firstCandidate 
                // has dropped to 0, replace firstCandidate by i 
                // and reset its count to 1.
                firstCandidate = i;
                cntFirstCandidate = 1;
            }
            else if (cntSecondCandidate == 0)
            {
                // Since the occurrence count of secondCandidate 
                // has dropped to 0, replace secondCandidate by i 
                // and reset its count to 1.
                secondCandidate = i;
                cntSecondCandidate = 1;
            }
            else
            {
                // (i != firstCandidate) && (i != secondCandidate) && 
                // (cntFirstCandidate > 0) && (cntSecondCandidate > 0)
                // Decrease both counts by 1.
                cntFirstCandidate--;
                cntSecondCandidate--;
            }
        }

        // Scan the numbers one by one and verify whether the two candidates 
        // are indeed majority elements.
        cntFirstCandidate = 0;
        cntSecondCandidate = 0;
        for (auto& i : nums)
        {
            if (i == firstCandidate)
            {
                cntFirstCandidate++;
            }
            else if (i == secondCandidate)
            {
                cntSecondCandidate++;
            }
        }

        if (cntFirstCandidate > nums.size() / 3)
        {
            res.push_back(firstCandidate);
        }
        if (cntSecondCandidate > nums.size() / 3)
        {
            res.push_back(secondCandidate);
        }

        return res;
    }
};