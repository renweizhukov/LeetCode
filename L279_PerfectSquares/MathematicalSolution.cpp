// Copied from https://leetcode.com/discuss/57066/4ms-c-code-solve-it-mathematically
class Solution
{
private:
    int is_square(int n)
    {
        int sqrt_n = (int)(sqrt(n));
        return (sqrt_n*sqrt_n == n);
    }

public:
    // Based on Lagrange's Four Square theorem, there 
    // are only 4 possible results: 1, 2, 3, 4.
    int numSquares(int n)
    {
        // If n is a perfect square, return 1.
        if (is_square(n))
        {
            return 1;
        }

        // The result is 4 if n can be written in the 
        // form of 4^k*(8*m + 7).
        while ((n & 3) == 0) // n%4 == 0  
        {
            n >>= 2;
        }
        if ((n & 7) == 7) // n%8 == 7
        {
            return 4;
        }

        // Check whether 2 is the result.
        int sqrt_n = (int)(sqrt(n));
        for (int i = 1; i <= sqrt_n; i++)
        {
            if (is_square(n - i*i))
            {
                return 2;
            }
        }

        return 3;
    }
};