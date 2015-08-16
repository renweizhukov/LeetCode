class Solution
{
public:
    // If num is 0, then the one-digit sum is 0; 
    // otherwise, as num increases from 1, the 
    // one-digit sum will repeat from 1 to 9 periodically. 
    int addDigits(int num)
    {
        if (num <= 0)
        {
            return num;
        }
        else
        {
            return num % 9 + (num % 9 == 0) * 9;
        }
    }
};