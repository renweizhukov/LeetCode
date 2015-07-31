class Solution
{
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target)
    {
        int cntRows = matrix.size();
        if (cntRows == 0)
        {
            // The matrix has zero row.
            return false;
        }

        int cntColumns = matrix[0].size();
        if (cntColumns == 0)
        {
            // The matrix has zero column.
            return false;
        }

        // Find the first row with its tail element matrix[][cntColumns - 1]
        // larger than or equal to target. Time complexity: O(log(m)).
        int startRow = 0;
        int endRow = cntRows - 1;
        int firstLargerTailRow = cntRows;
        if (matrix[endRow][cntColumns - 1] < target)
        {
            // matrix[endRow][cntColumns - 1] is the largest element in the 
            // matrix, so if target is even larger, it can't be found in 
            // the matrix.
            return false;
        }
        else if (matrix[startRow][cntColumns - 1] > target)
        {
            // The first row is the row we are looking for.
            firstLargerTailRow = 0;
        }
        else
        {
            // matrix[startRow][cntColumns - 1] <= target 
            // <= matrix[endRow][cntColumns - 1]

            // Use binary search to find the row. 
            while (startRow < endRow)
            {
                int midRow = (startRow + endRow) / 2;
                if (matrix[midRow][cntColumns - 1] == target)
                {
                    return true;
                }
                else if (matrix[midRow][cntColumns - 1] > target)
                {
                    // We don't set endRow to midRow - 1 because 
                    // we intend to make sure that 
                    // matrix[endRow][cntColumns - 1] >= target.
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

        // Find the last row with its head element matrix[][0] 
        // smaller than or equal to target. Time complexity: O(log(m)).
        startRow = 0;
        endRow = cntRows - 1;
        int lastSmallerHeadRow = -1;
        if (matrix[startRow][0] > target)
        {
            // matrix[startRow][0] is the smallest element in the matrix, 
            // so if target is even smaller, it can't be found in the matrix.
            return false;
        }
        else if (matrix[endRow][0] < target)
        {
            // The last row is the row we are looking for.
            lastSmallerHeadRow = endRow;
        }
        else
        {
            // matrix[startRow][0] <= target <= matrix[endRow][0]
            // Use the binary search to find the row.
            while (startRow < endRow)
            {
                // +1 is required; otherwise if endRow = startRow + 1 
                // and matrix[startRow][0] < target, we will enter 
                // the infinite loops.
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
                    // We don't set startRow to midRow + 1 because 
                    // we intend to make sure that 
                    // matrix[startRow][0] <= target.
                    startRow = midRow;
                }
            }

            lastSmallerHeadRow = endRow;
        }

        // If target exists in the matrix, it must exist between row firstLargerTailRow 
        // and row lastSmallerHeadRow. Time complexity: O(m*log(n)).
        for (int rowIndex = firstLargerTailRow; rowIndex <= lastSmallerHeadRow; rowIndex++)
        {
            int startColumn = 0;
            int endColumn = cntColumns - 1;

            // Use binary search to find target within each row.
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