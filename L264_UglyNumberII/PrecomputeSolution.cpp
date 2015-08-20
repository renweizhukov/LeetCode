class Solution
{
public:
    int nthUglyNumber(int n)
    {
        // Use a static vector so that we only need to compute all the ugly 
        // numbers within the int range (i.e., <= INT_MAX) once.
        static vector<long> uglyNumbers;
        long power2 = 0;   // ugly numbers only have 2 as the prime factors
        long power23 = 0;  // ugly numbers only have 2 and 3 as the prime factors
        long power235 = 0; // ugly numbers only have 2, 3, and 5 as the prime factors

        if (uglyNumbers.empty())
        {
            for (power2 = 1; power2 <= INT_MAX; power2 *= 2)
            {
                for (power23 = power2; power23 <= INT_MAX; power23 *= 3)
                {
                    for (power235 = power23; power235 <= INT_MAX; power235 *= 5)
                    {
                        uglyNumbers.push_back(power235);
                    }
                }
            }

            sort(uglyNumbers.begin(), uglyNumbers.end());
        }

        return uglyNumbers[n - 1];
    }
};