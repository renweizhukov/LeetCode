class Solution
{
public:
    vector<int> majorityElement(vector<int>& nums)
    {
        vector<int> res;
        int firstCandidate = 0;
        int cntFirstCandidate = 0;
        int secondCandidate = 1;
        int cntSecondCandidate = 0;

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
            else if (cntFirstCandidate == 0)
            {
                firstCandidate = i;
                cntFirstCandidate = 1;
            }
            else if (cntSecondCandidate == 0)
            {
                secondCandidate = i;
                cntSecondCandidate = 1;
            }
            else
            {
                cntFirstCandidate--;
                cntSecondCandidate--;
            }
        }

        cntFirstCandidate = 0;
        cntSecondCandidate = 0;
        for (auto& i : nums)
        {
            if (i == firstCandidate)
            {
                cntFirstCandidate++;
            }

            if (i == secondCandidate)
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