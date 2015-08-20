class Solution
{
public:
    bool isUgly(int num)
    {
        if (num <= 0)
        {
            // Non-positive numbers are not ugly.
            return false;
        }
        else if (num <= 6)
        {
            // 1, 2, 3, 4, 5, 6 are ugly numbers.
            return true;
        }
        else
        {
            // Remove the factor "2" from the number.
            while (num % 2 == 0)
            {
                num /= 2;
            }

            // Remove the factor "3" from the number.
            while (num % 3 == 0)
            {
                num /= 3;
            }

            // Remove the factor "5" from the number.
            while (num % 5 == 0)
            {
                num /= 5;
            }

            // If 2, 3, and 5 are the only prime factors 
            // of num, num should be 1 now; otherwise 
            // num should be a prime number bigger than 1.
            return (num == 1);
        }
    }
};