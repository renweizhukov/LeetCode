class Solution
{
public:
    int countDigitOne(int n)
    {
        if (n <= 0)
        {
            return 0;
        }

        int res = 0;
        int tmp = n;
        // The base of the digit in n which is a power of 10.
        int base = 1;
        // The least significant digit of tmp.
        int lsd = 0;

        // Count the occurrences of digit '1' from the least significant 
        // digit of n to the most significant digit of n.
        while (tmp > 0)
        {
            // Get the least significant digit of tmp which is the digit 
            // in n with the "base", e.g., digit '2' in "120" with base 10. 
            lsd = tmp % 10;
            tmp /= 10;

            if (lsd > 1)
            {
                // If lsd > 1, we need to count all the '1' occurrences 
                // in base*(10*tmp + 1).
                res += (base*(tmp + 1));
            }
            else if (lsd == 1)
            {
                // If lsd == 1, we need to count "part" of the '1' occurrences
                // in base*(10*tmp + 1).
                res += base*tmp + (n - base*(10 * tmp + 1) + 1);
            }
            else
            {
                // If lsd == 0, we need to exclude the '1' occurrences
                // in base*(10*tmp + 1).
                res += base*tmp;
            }

            base *= 10;
        }

        return res;
    }
};