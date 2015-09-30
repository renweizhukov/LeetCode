class Solution
{
    // num: the input digit string.
    // start: the start index of num which needs to be processed.
    // target: the input target value.
    // currResVal: the result value of the substring before "start".
    // rightmostProduct: the rightmost product of the substring 
    //     before "start", e.g. for "1 + 2 * 3", 
    //     rightmostProduct = 2*3 = 6.
    // prevOperator: the operator previous to the current number.
    // res: the output vector of strings.
    // oneResList: a list of strings which contains one result 
    //     string, e.g., "1+2*3" is kept as "1+" -> "2*" -> "3". 
    void AddOperatorsRecursive(
        string& num,
        int start,
        int target,
        long currResVal,
        long rightmostProduct,
        char prevOperator,
        vector<string>& res,
        list<string>& oneResList)
    {
        int len = num.length();
        if (start == len)
        {
            // We have passed the end of num.
            if (currResVal == target)
            {
                // We have found one result string whose result 
                // matches target.

                // Flatten the string list to obtain one result 
                // string.
                string oneRes;
                for (auto& str : oneResList)
                {
                    oneRes += str;
                }

                res.push_back(oneRes);
            }

            return;
        }

        // If the first character is '0', currNum can only be 0; otherwise 
        // currNum can be any number starting from "start" and ending 
        // before/at "len - 1".
        int maxEndIndex = (num[start] != '0') ? len - 1 : start;
        long currNum = 0;
        long newResVal = 0;
        long newRightmostProduct = 0;
        for (int end = start; end <= maxEndIndex; end++)
        {
            // Add one more digit to currNum.
            currNum = 10 * currNum + (num[end] - '0');

            // Update newResVal and newRightmostProduct.
            if (prevOperator == '+')
            {
                newResVal = currResVal + currNum;
                newRightmostProduct = currNum;
            }
            else if (prevOperator == '-')
            {
                newResVal = currResVal - currNum;
                // To take into account '-', newRightmostProduct is 
                // opposite to currNum.
                newRightmostProduct = -currNum;
            }
            else
            {
                // Before we process currNum, we have already added 
                // rightmostProduct to currResVal. Since the correct 
                // value to be added is rightmostProduct*currNum, we 
                // should add rightmostProduct*(currNum - 1) here.
                newResVal = currResVal + rightmostProduct*(currNum - 1);
                newRightmostProduct = rightmostProduct*currNum;
            }

            if (end < len - 1)
            {
                // Assume that next operator is '+'.
                oneResList.push_back(num.substr(start, end - start + 1) + '+');
                AddOperatorsRecursive(
                    num,
                    end + 1,
                    target,
                    newResVal,
                    newRightmostProduct,
                    '+',
                    res,
                    oneResList);
                oneResList.pop_back();

                // Assume that next operator is '-'.
                oneResList.push_back(num.substr(start, end - start + 1) + '-');
                AddOperatorsRecursive(
                    num,
                    end + 1,
                    target,
                    newResVal,
                    newRightmostProduct,
                    '-',
                    res,
                    oneResList);
                oneResList.pop_back();

                // Assume that next operator is '*'.
                oneResList.push_back(num.substr(start, end - start + 1) + '*');
                AddOperatorsRecursive(
                    num,
                    end + 1,
                    target,
                    newResVal,
                    newRightmostProduct,
                    '*',
                    res,
                    oneResList);
                oneResList.pop_back();
            }
            else
            {
                // We have reached the end of num.
                oneResList.push_back(num.substr(start));
                AddOperatorsRecursive(
                    num,
                    end + 1,
                    target,
                    newResVal,
                    newRightmostProduct,
                    '+',
                    res,
                    oneResList);
                oneResList.pop_back();
            }
        }
    }

public:
    vector<string> addOperators(string num, int target)
    {
        vector<string> res;
        list<string> oneResList;

        AddOperatorsRecursive(
            num,
            0,      // start
            target,
            0,      // currResVal
            0,      // rightmostProduct
            '+',    // prevOperator
            res,
            oneResList);

        return res;
    }
};