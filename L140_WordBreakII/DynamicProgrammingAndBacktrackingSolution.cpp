class Solution
{
    vector<bool> GetWordBreakFlags(string& s, unordered_set<string>& wordDict)
    {
        int len = s.length();
        // wordBreakFlags[i] = the flag which indicates whether s.substr(i) 
        // can be broken into words in wordDict. Note that although 
        // s.substr(len) is an empty string, we assume that wordBreakFlags[len] 
        // is true for simplifying the code logic.
        vector<bool> wordBreakFlags(len + 1);
        // A vector of string indexes where the corresponding wordBreakFlags is  
        // true.
        vector<int> trueWordBreakFlagIndexes({ len });
        auto it = wordDict.end();

        // Set wordBreakFlags[len] to true.
        wordBreakFlags.back() = true;
        // Compute wordBreakFlags backwards from len - 1.
        for (int start = len - 1; start >= 0; start--)
        {
            // We only need to check the string indexes where the corresponding 
            // wordBreakFlags is true.
            for (auto& i : trueWordBreakFlagIndexes)
            {
                it = wordDict.find(s.substr(start, i - start));
                if (it != wordDict.end())
                {
                    wordBreakFlags[start] = true;
                    trueWordBreakFlagIndexes.push_back(start);
                    break;
                }
            }
        }

        return wordBreakFlags;
    }

    void WordBreakRecursive(
        string& s,
        int start,
        unordered_set<string>& wordDict,
        vector<bool>& wordBreakFlags,
        string& oneRes,
        vector<string>& allRes)
    {
        int len = s.length();
        if (start == len)
        {
            // We have found one broken way of words in wordDict. 

            // Remove the extra space after the last word in wordDict.
            oneRes.pop_back();
            allRes.push_back(oneRes);
        }
        else
        {
            for (int i = start; i < len; i++)
            {
                if (wordBreakFlags[i + 1])
                {
                    // If s.substr(i + 1) can be broken into words in wordDict, then we 
                    // check whether s.substr(start, i - start + 1) is a word in wordDict.
                    auto it = wordDict.find(s.substr(start, i - start + 1));
                    if (it != wordDict.end())
                    {
                        string tmp = oneRes;
                        // Append the word in wordDict plus a space to oneRes.
                        oneRes += (*it + " ");
                        WordBreakRecursive(s, i + 1, wordDict, wordBreakFlags, oneRes, allRes);
                        // Restore oneRes;
                        oneRes = tmp;
                    }
                }
            }
        }
    }

public:
    vector<string> wordBreak(string s, unordered_set<string>& wordDict)
    {
        vector<string> res;
        if (s.empty())
        {
            return res;
        }

        // wordBreakFlags[i] = the flag which indicates whether s.substr(i) 
        // can be broken into words in wordDict.
        vector<bool> wordBreakFlags = GetWordBreakFlags(s, wordDict);
        if (!wordBreakFlags.front())
        {
            // Since s can't be broken into words in wordDict, return an 
            // empty vector of strings.
            return res;
        }

        // Recursively get all the possible broken ways of words in wordDict.
        string oneRes;
        WordBreakRecursive(
            s,
            0,
            wordDict,
            wordBreakFlags,
            oneRes,
            res);

        return res;
    }
};