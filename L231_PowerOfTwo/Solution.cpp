class Solution
{
public:
    bool isPowerOfTwo(int n)
    {
        if (n <= 0)
        {
            // An integer can't be a power of two if it
            // isn't positive.
            return false;
        }
        else
        {
            // If a positive integer n is a power of two, 
            // it has exactly one '1' in its binary 
            // representation and n & (n - 1) will be zero; 
            // otherwise, it has either 0 or more than one '1'
            // in its binary representation and n & (n - 1) 
            // will be non-zero.
            return !(n & (n - 1));
        }
    }
};