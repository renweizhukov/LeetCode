class Solution
{
public:
    int addDigits(int num)
    {
        // num should be non-negative, so if num 
        // is negative, return num immediately.
        if (num < 0)
        {
            return num;
        }

        // If num is within the range [0, 9], then 
        // we have obtained the one-digit result.
        while (num > 9)
        {
            // Calculate the digit sum of num.
            int digitSum = 0;
            while (num > 0)
            {
                digitSum += num % 10;
                num /= 10;
            }

            num = digitSum;
        }

        return num;
    }
};