class Solution
{
    string threeDigitGroupToWords(int num)
    {
        // The first 10 Words are used for ones and hundreds, and 
        // the following 10 words are used numbers between 10 and 20.
        const static char* lessThanTwenty[] =
        { "", "One ", "Two ", "Three ", "Four ", "Five ",
        "Six ", "Seven ", "Eight ", "Nine ",
        "Ten ", "Eleven ", "Twelve ", "Thirteen ", "Fourteen ",
        "Fifteen ", "Sixteen ", "Seventeen ", "Eighteen ", "Nineteen " };
        // Words used for the tens of numbers between 21 and 99.
        const static char* Tens[] =
        { "", "", "Twenty ", "Thirty ", "Forty ", "Fifty ", "Sixty ",
        "Seventy ", "Eighty ", "Ninety " };

        string res;

        // Get the hundred digit.
        res += lessThanTwenty[num / 100];
        if (!res.empty())
        {
            // Add the hundred unit if num >= 100.
            res += "Hundred ";
        }

        // Remove the hundred digit and keep the ten and one digits.
        num -= (num / 100 * 100);
        if (num == 0)
        {
            // If num is a multiple of 100, return immediately and 
            // don't need to convert the ten and one digits.
            return res;
        }

        if (num < 20)
        {
            // The ten digit is 0 or 1.
            res += lessThanTwenty[num];
        }
        else
        {
            // The ten digit is greater than 1.
            res += Tens[num / 10];

            num %= 10;
            if (num == 0)
            {
                // If num is a multiple of 10, return immediately 
                // and don't need to conver the one digit.
                return res;
            }

            res += lessThanTwenty[num];
        }

        return res;
    }

public:
    string numberToWords(int num)
    {
        if (num < 0)
        {
            // Negative number is an invalid input.
            return "Invalid";
        }
        else if (num == 0)
        {
            // (num == 0) is the only case that "Zero" will be contained 
            // in the output string.
            return "Zero";
        }

        // For a positive number, we group the number by thousands (3 digits).
        // We use stack here because we need to first obtain the word for the 
        // most significant 3-digit group.
        stack<int> threeDigitGroups;
        while (num > 0)
        {
            threeDigitGroups.push(num % 1000);
            num /= 1000;
        }

        // INT_MAX = 2^31 - 1 = 2147483647, so the greatest group unit is "Billion".
        const static char* groupUnits[] = { "", "Thousand ", "Million ", "Billion " };
        int groupUnitIndex = threeDigitGroups.size() - 1;

        // Convert the 3-digit group into a word and append its unit.
        string res;
        while (!threeDigitGroups.empty())
        {
            int threeDigitGroup = threeDigitGroups.top();
            threeDigitGroups.pop();

            // If this 3-digit group is 0, then we don't append anything to the 
            // result string.
            if (threeDigitGroup > 0)
            {
                res += threeDigitGroupToWords(threeDigitGroup);
                res += groupUnits[groupUnitIndex];
            }

            // Move the group unit to the previous one.
            groupUnitIndex--;
        }

        res.pop_back();
        return res;
    }
};