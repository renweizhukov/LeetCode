class Solution
{
public:
    int nthUglyNumber(int n)
    {
        if (n <= 0)
        {
            return 0;
        }

        // If we call nthUglyNumber once, the static definitions 
        // won't save us any time. But if we call nthUglyNumber 
        // multiple times, the static definitions will save us 
        // the time of repetitive computations of the same ugly 
        // numbers. Consider the following calling sequence:
        // (1) nthUglyNumber(10): the static vector uglyNumbers 
        //     will be expanded to 10 elements;
        // (2) nthUglyNumber(5): will return uglyNumbers[4] immediately;
        // (3) nthUglyNumber(15): will just need to compute 
        //     uglyNumber[10],..., uglyNumber[14].
        static vector<int> uglyNumbers({ 1 });

        static int c2 = 2;
        static int c3 = 3;
        static int c5 = 5;

        static int i2 = 0;
        static int i3 = 0;
        static int i5 = 0;

        while (n > uglyNumbers.size())
        {
            uglyNumbers.push_back(min(c2, min(c3, c5)));

            static int last = 1;
            last = uglyNumbers.back();

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

        return uglyNumbers[n - 1];
    }
};