class Solution 
{
    int romanChToInt(const char ch)
    {
        switch (ch)
        {
        case 'I':
            return 1;
        case 'V':
            return 5;
        case 'X':
            return 10;
        case 'L':
            return 50;
        case 'C':
            return 100;
        case 'D':
            return 500;
        case 'M':
            return 1000;
        default:
            return 0;
        }
    }

public:
    int romanToInt(string s)
    {
        int n = s.length();
        if (n == 0)
        {
            return 0;
        }

        int ret = 0;
        // Integer value of current Roman character.
        int curr = romanChToInt(s[0]);
        // Integer value of next Roman character.
        int next = 0;

        for (int i = 0; i < n - 1; i++)
        {
            next = romanChToInt(s[i + 1]);
            if (curr >= next)
            {
                ret += curr;
            }
            else
            {
                // If next Roman character is larger than 
                // the current Roman character, we should 
                // substract curr from ret.
                ret -= curr;
            }

            curr = next;
        }

        // Add the last Roman character.
        ret += curr;

        return ret;
    }
};