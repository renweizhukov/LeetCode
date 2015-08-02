class Solution
{
public:
    bool isAnagram(string s, string t)
    {
        if (s.length() != t.length())
        {
            return false;
        }

        int chCnt[26] = { 0 };
        for (int i = 0; i < s.length(); i++)
        {
            chCnt[s[i] - 'a']++;
        }

        for (int i = 0; i < t.length(); i++)
        {
            if (chCnt[t[i] - 'a'] > 0)
            {
                chCnt[t[i] - 'a']--;
            }
            else
            {
                return false;
            }
        }

        return true;
    }
};