class Solution
{
public:
    int nthUglyNumber(int n)
    {
        if (n <= 0)
        {
            return 0;
        }

        // uglyNumbers will store the first n ugly numbers. Note that 
        // the first ugly number is 1.
        vector<int> uglyNumbers(n, 1);

        // c2: the candidate for next ugly number = 2*uglyNumbers[i2].
        // c3: the candidate for next ugly number = 3*uglyNumbers[i3].
        // c5: the candidate for next ugly number = 5*uglyNumbers[i5].
        int c2 = 2;
        int c3 = 3;
        int c5 = 5;

        // i2: the index of uglyNumber which is used for obtaining c2.
        // i3: the index of uglyNumber which is used for obtaining c3.
        // i5: the index of uglyNumber which is used for obtaining c5.
        int i2 = 0;
        int i3 = 0;
        int i5 = 0;

        for (int i = 1; i < n; i++)
        {
            // Select the smallest candiate as the next ugly number.
            uglyNumbers[i] = min(c2, min(c3, c5));
            int last = uglyNumbers[i];

            // Update the candidates. Since only numbers which are 
            // greater than last ugly number can be valid candidates 
            // for next ugly number, we will move forward i2, i3, and 
            // i5 until c2, c3, and c5 are greater than "last".
            while (c2 <= last)
            {
                c2 = 2 * uglyNumbers[++i2];
            }

            while (c3 <= last)
            {
                c3 = 3 * uglyNumbers[++i3];
            }

            while (c5 <= last)
            {
                c5 = 5 * uglyNumbers[++i5];
            }
        }

        return uglyNumbers.back();
    }
};