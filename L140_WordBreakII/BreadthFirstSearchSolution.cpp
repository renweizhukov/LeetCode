class Solution
{
    void BuildPathFromPrevMap(
        string &s,
        unordered_map<int, vector<int>> &prevMap,
        vector<int> &pathIndexes,
        vector<string> &res)
    {
        if (pathIndexes.back() == 0)
        {
            // We have reached node 0. By reversely iterating pathIndexes, we get 
            // one possible sentence.
            string path;
            for (int i = pathIndexes.size() - 1; i > 0; i--)
            {
                path.append(s.substr(pathIndexes[i],
                    pathIndexes[i - 1] - pathIndexes[i]));
                if (i > 1)
                {
                    path.push_back(' ');
                }
            }
            res.push_back(path);

            return;
        }

        for (auto &i : prevMap[pathIndexes.back()])
        {
            // Try every possible previous node.
            pathIndexes.push_back(i);
            BuildPathFromPrevMap(s, prevMap, pathIndexes, res);
            // Restore pathIndexes for next iteration.
            pathIndexes.pop_back();
        }
    }

public:
    vector<string> wordBreak(
        string s,
        unordered_set<string> &dict)
    {
        vector<string> res;
        int len = s.length();
        if (len == 0)
        {
            return res;
        }

        // Construct a directed graph where each node i represents s.substr(0, i). 
        // There is a link from node i to node j (i < j) if and only if both s.substr(0, i) 
        // s.substr(0, j) can be broken into dictionary words. The solution is 
        // essentially all the paths from node 0 to node len. This map will keep 
        // the previous nodes on those paths for each node.
        unordered_map<int, vector<int>> prevMap;

        // Use breadth-first search to find all the paths from node 0 to node len.
        queue<int> currSearch;
        currSearch.push(0); // 0 represents s.substr(0, 0), i.e., an empty string.
        int currSearchSize = 1;
        while (currSearchSize > 0)
        {
            for (int i = 0; i < currSearchSize; i++)
            {
                int j = currSearch.front();
                currSearch.pop();

                for (int k = j + 1; k <= len; k++)
                {
                    auto it = dict.find(s.substr(j, k - j));
                    if (it != dict.end())
                    {
                        // j is a previous node of k.
                        auto itMap = prevMap.find(k);
                        if (itMap == prevMap.end())
                        {
                            prevMap.insert(make_pair(k, vector<int>({ j })));

                            // This is the first time that we see k and k is not 
                            // the end of the string, so we need to add k to the 
                            // search queue.
                            if (k != len)
                            {
                                currSearch.push(k);
                            }
                        }
                        else
                        {
                            itMap->second.push_back(j);
                        }
                    }
                }
            }

            currSearchSize = currSearch.size();
        }

        // Backtrack from node len to node 0 to get all the paths.
        vector<int> pathIndexes({ len });
        BuildPathFromPrevMap(s, prevMap, pathIndexes, res);

        return res;
    }
};