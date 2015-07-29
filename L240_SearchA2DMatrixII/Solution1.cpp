class Solution
{
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target)
    {
        int cntRows = matrix.size();
        if (cntRows == 0)
        {
            return false;
        }

        int cntColumns = matrix[0].size();
        if (cntColumns == 0)
        {
            return false;
        }

        int rowIndex = 0;
        int columnIndex = cntColumns - 1;
        while ((rowIndex < cntRows) && (columnIndex >= 0))
        {
            if (matrix[rowIndex][columnIndex] == target)
            {
                return true;
            }
            else if (matrix[rowIndex][columnIndex] < target)
            {
                rowIndex++;
            }
            else
            {
                // matrix[rowIndex][columnIndex] > target
                columnIndex--;
            }
        }

        return false;
    }
};