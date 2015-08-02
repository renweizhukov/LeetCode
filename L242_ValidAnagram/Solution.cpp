class Solution
{
public:
    bool isAnagram(string s, string t)
    {
        // If s and t have different lengths, t can't  
        // an anagram of s.
        if (s.length() != t.length())
        {
            return false;
        }

        // chCnt[ch] = occurrence count of character 
        // 'a' + ch in s.
        int chCnt[26] = { 0 };
        for (int i = 0; i < s.length(); i++)
        {
            chCnt[s[i] - 'a']++;
        }

        // If t is an anagram of s, then chCnt[ch] 
        // for each ch will be 0 when all the characters 
        // of t have been counted. If not, then 
        // chCnt[ch] will be 0 for some ch before 
        // all the characters of t have been counted.
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