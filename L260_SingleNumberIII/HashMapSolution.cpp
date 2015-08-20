class Solution
{
public:
    vector<int> singleNumber(vector<int>& nums)
    {
        vector<int> res;

        unordered_set<int> numSet;
        for (auto& i : nums)
        {
            auto it = numSet.find(i);
            if (it == numSet.end())
            {
                // If this is the first time to see the number, 
                // add it to the unordered set.
                numSet.insert(i);
            }
            else
            {
                // If this is the second time to see the number,
                // it is a duplicate and should be removed from 
                // the unordered set.
                numSet.erase(it);
            }
        }

        for (auto& i : numSet)
        {
            res.push_back(i);
        }

        return res;
    }
};