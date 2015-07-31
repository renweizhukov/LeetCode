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

        int startRow = 0;
        int endRow = cntRows - 1;
        int firstLargerTailRow = cntRows;
        if (matrix[endRow][cntColumns - 1] < target)
        {
            return false;
        }
        else if (matrix[startRow][cntColumns - 1] > target)
        {
            firstLargerTailRow = 0;
        }
        else
        {
            // matrix[startRow][cntColumns - 1] <= target 
            // <= matrix[endRow][cntColumns - 1]
            while (startRow < endRow)
            {
                int midRow = (startRow + endRow) / 2;
                if (matrix[midRow][cntColumns - 1] == target)
                {
                    return true;
                }
                else if (matrix[midRow][cntColumns - 1] > target)
                {
                    endRow = midRow;
                }
                else
                {
                    // matrix[midRow][cntColumns - 1] < target
                    startRow = midRow + 1;
                }
            }

            firstLargerTailRow = startRow;
        }

        startRow = 0;
        endRow = cntRows - 1;
        int lastSmallerHeadRow = -1;
        if (matrix[startRow][0] > target)
        {
            return false;
        }
        else if (matrix[endRow][0] < target)
        {
            lastSmallerHeadRow = endRow;
        }
        else
        {
            // matrix[startRow][0] <= target <= matrix[endRow][0]
            while (startRow < endRow)
            {
                int midRow = (startRow + endRow + 1) / 2;
                if (matrix[midRow][0] == target)
                {
                    return true;
                }
                else if (matrix[midRow][0] > target)
                {
                    endRow = midRow - 1;
                }
                else
                {
                    // matrix[midRow][0] < target
                    startRow = midRow;
                }
            }

            lastSmallerHeadRow = endRow;
        }

        for (int rowIndex = firstLargerTailRow; rowIndex <= lastSmallerHeadRow; rowIndex++)
        {
            int startColumn = 0;
            int endColumn = cntColumns - 1;
            while (startColumn <= endColumn)
            {
                int midColumn = (startColumn + endColumn) / 2;
                if (matrix[rowIndex][midColumn] == target)
                {
                    return true;
                }
                else if (matrix[rowIndex][midColumn] > target)
                {
                    endColumn = midColumn - 1;
                }
                else
                {
                    // matrix[rowIndex][midColumn] < target
                    startColumn = midColumn + 1;
                }
            }
        }

        return false;
    }
};