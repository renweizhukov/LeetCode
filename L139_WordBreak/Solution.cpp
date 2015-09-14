class Solution
{
public:
    bool wordBreak(string s, unordered_set<string> &dict)
    {
        int len = s.length();
        if (len == 0)
        {
            return false;
        }

        // wordBreakFlags[i] = whether s[0,...,i] can be segmented 
        // into a space-separated sequence of one or more 
        // dictionary words.
        vector<bool> wordBreakFlags(len);
        // Currently known indexes at which wordBreakFlags is true.
        vector<int> trueFlagIndexes;
        auto it = dict.end();

        for (int i = 0; i < len; i++)
        {
            it = dict.find(s.substr(0, i + 1));
            if (it != dict.end())
            {
                // s[0,...,i] itself is a dictionary word.
                wordBreakFlags[i] = true;
                trueFlagIndexes.push_back(i);
            }
            else
            {
                // Try every known index at which wordBreakFlags is true.
                for (auto &j : trueFlagIndexes)
                {
                    it = dict.find(s.substr(j + 1, i - j));
                    // Check the word after j is in dictionary.
                    if (it != dict.end())
                    {
                        wordBreakFlags[i] = true;
                        trueFlagIndexes.push_back(i);
                        break;
                    }
                }
            }
        }

        return wordBreakFlags.back();
    }
};