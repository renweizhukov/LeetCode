// Forward declaration of isBadVersion API.
bool isBadVersion(int version);

class Solution
{
public:
    int firstBadVersion(int n)
    {
        // If n is non-positive, the input n is invalid.
        if (n <= 0)
        {
            return 0;
        }

        // If 1 is a bad version, it must be the minimum bad version.
        if (isBadVersion(1))
        {
            return 1;
        }

        // If n is not a bad version, there is no bad version.
        if (!isBadVersion(n))
        {
            return 0;
        }

        // Use the binary search to find the minimum bad version.
        // Note that since we have reached here, 1 must be a good 
        // version and n must be a bad version.
        int goodVersion = 1;
        int badVersion = n;
        while (badVersion - goodVersion > 1)
        {
            // We don't use (goodVersion + badVersion)/2 because 
            // (goodVersion + badVersion) may overflow (i.e., > INT_MAX).
            int midVersion = goodVersion + (badVersion - goodVersion) / 2;
            if (isBadVersion(midVersion))
            {
                badVersion = midVersion;
            }
            else
            {
                goodVersion = midVersion;
            }
        }

        return badVersion;
    }
};