class Solution
{
public:
    int nthUglyNumber(int n)
    {
        // Since an ugly number only have 2, 3, and 5 
        // as its prime factor, the n-th ugly number 
        // can be obtained by multiplying a smaller 
        // ugly number by 2, 3, or 5.

        // The first ugly number is 1. Note that we use 
        // long to avoid the overflow.
        set<long> uglyNumbers({ 1 });
        long res = 0;

        // Keep removing the smallest ugly number from 
        // the set until we get the n-th one.
        while (n-- > 0)
        {
            // Since the set is sorted, it is pointed 
            // to the smallest ugly number in the set.
            auto it = uglyNumbers.begin();
            res = *it;

            // Remove the currently smallest ugly number 
            // from the set.
            uglyNumbers.erase(it);

            // Insert 2*res, 3*res, and 5*res into the set. 
            // If either of them already exists in the set, 
            // its insertion will be ignored.
            uglyNumbers.insert(2 * res);
            uglyNumbers.insert(3 * res);
            uglyNumbers.insert(5 * res);
        }

        return res;
    }
};