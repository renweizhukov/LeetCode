class Solution
{
    // Separate the operands and the operators ('+', '-', '*')
    // in the input string.
    void GetOperandsAndOperatorsFromString(
        string &input,
        vector<int> &operands,
        vector<char> &operators)
    {
        int number = 0;
        for (int i = 0; i <= input.length(); i++)
        {
            if ((input[i] >= '0') && (input[i] <= '9'))
            {
                // This character is a digit and add it to 
                // the number.
                number = 10 * number + (input[i] - '0');
            }
            else if ((input[i] == '+') ||
                (input[i] == '-') ||
                (input[i] == '*'))
            {
                // This character is an operator and it implies 
                // the end of the previous number. Add the number 
                // to the operand vector and reset the number. Also 
                // add the operator to the operator vector.
                operands.push_back(number);
                number = 0;

                operators.push_back(input[i]);
            }
            else if (input[i] == '\0')
            {
                // This is the end of the input string. Add the 
                // last number to the operand vector.
                operands.push_back(number);
            }
        }
    }

public:
    vector<int> diffWaysToCompute(string input)
    {
        vector<int> operands;
        vector<char> operators;

        // Get the operands and operators from the input string.
        GetOperandsAndOperatorsFromString(input, operands, operators);

        // Note that count of operands = cnt of operators + 1.
        int cntOperators = operators.size();

        // dp[operandIndex][cntUsedOperators] = vector of all possible results 
        // computed from the substring starting from operand "operandIndex" and 
        // including the subsequent "cntUsedOperators" operators and operands.
        vector<vector<vector<int>>> dp(cntOperators + 1, vector<vector<int>>());

        // When cntUsedOperators = 0, dp[operandIndex][0] = operands[operandIndex].
        for (int operandIndex = 0; operandIndex < cntOperators + 1; operandIndex++)
        {
            dp[operandIndex].push_back(vector<int>{operands[operandIndex]});
        }

        // cntUsedOperators = 1,...,cntOperators.
        for (int cntUsedOperators = 1; cntUsedOperators <= cntOperators; cntUsedOperators++)
        {
            // Note that operandIndex starts from 0 and ends at the last operand which 
            // is followed by "cntUsedOperators" operators and operands.
            for (int operandIndex = 0;
                operandIndex < cntOperators + 1 - cntUsedOperators;
                operandIndex++)
            {
                // dp[operandIndex][cntUsedOperators] = the union of all outcomes for each 
                // possible last operator.
                vector<int> tmpRes;
                for (int lastOperatorIndex = operandIndex; lastOperatorIndex < operandIndex + cntUsedOperators; lastOperatorIndex++)
                {
                    // The last operator breaks the substring into two halves. 
                    // dp[operandIndex][lastOperatorIndex - operandIndex] = 
                    //  all the outcomes of the first half.
                    // dp[lastOperatorIndex + 1][cntUsedOperators - 1 - (lastOperatorIndex - operandIndex)] = 
                    //  all the outcomes of the second half.
                    for (auto &x : dp[operandIndex][lastOperatorIndex - operandIndex])
                    {
                        for (auto &y : dp[lastOperatorIndex + 1][cntUsedOperators - 1 - (lastOperatorIndex - operandIndex)])
                        {
                            if (operators[lastOperatorIndex] == '+')
                            {
                                tmpRes.push_back(x + y);
                            }
                            else if (operators[lastOperatorIndex] == '-')
                            {
                                tmpRes.push_back(x - y);
                            }
                            else
                            {
                                tmpRes.push_back(x * y);
                            }
                        }
                    }
                }

                dp[operandIndex].push_back(tmpRes);
            }
        }

        // The final result is all possible outcomes starting from operand 0 and including all operators.
        return dp[0][cntOperators];
    }
};