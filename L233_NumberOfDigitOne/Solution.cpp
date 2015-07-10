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
        int base = 1;
        int lsd = 0;
        while (tmp > 0)
        {
            lsd = tmp % 10;
            tmp /= 10;

            if (lsd > 1)
            {
                res += (base*(tmp + 1));
            }
            else if (lsd == 1)
            {
                res += base*tmp + (n - base*(10 * tmp + 1) + 1);
            }
            else
            {
                res += base*tmp;
            }

            base *= 10;
        }

        return res;
    }
};