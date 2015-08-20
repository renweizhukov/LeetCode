class Solution
{
public:
    vector<int> singleNumber(vector<int>& nums)
    {
        vector<int> res;

        // Assume that the two single numbers are x and y. 
        // XOR all the numbers and all the duplicates will 
        // be neutralized, so the result will be x^y.
        int xXorY = 0;
        for (auto& i : nums)
        {
            xXorY ^= i;
        }

        // Get the number which contains a single one bit, 
        // i.e., the lowest one bit of x^y.
        int lowestOneBit = xXorY & (~(xXorY - 1));

        // XOR all the numbers which has the lowest one bit 
        // of x^y. Assume that the lowest one bit of x^y 
        // comes from x. Then y won't be included in the 
        // xor operations. Since those duplicates which also  
        // have the lowest one bit of x^y are neutralized, 
        // the result will be x.
        int x = 0;
        for (auto& i : nums)
        {
            if (i & lowestOneBit)
            {
                x ^= i;
            }
        }

        // y = (x^y)^x.
        int y = xXorY ^ x;

        res.push_back(x);
        res.push_back(y);

        return res;
    }
};