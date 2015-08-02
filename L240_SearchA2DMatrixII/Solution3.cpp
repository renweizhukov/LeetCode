class Solution
{
    bool searchSubMatrixRecursive(
        vector<vector<int>> &matrix,
        int target,
        int startRow,
        int endRow,
        int startColumn,
        int endColumn)
    {
        if ((startRow > endRow) || (startColumn > endColumn))
        {
            return false;
        }

        if ((startRow == endRow) && (startColumn == endColumn))
        {
            return (matrix[startRow][startColumn] == target);
        }

        int midRow = (startRow + endRow) / 2;
        int midColumn = (startColumn + endColumn) / 2;
        if (matrix[midRow][midColumn] == target)
        {
            return true;
        }
        else if (matrix[midRow][midColumn] < target)
        {
            return ((searchSubMatrixRecursive(
                matrix,
                target,
                midRow + 1,
                endRow,
                midColumn + 1,
                endColumn)) ||
                (searchSubMatrixRecursive(
                matrix,
                target,
                startRow,
                midRow,
                midColumn + 1,
                endColumn)) ||
                (searchSubMatrixRecursive(
                matrix,
                target,
                midRow + 1,
                endRow,
                startColumn,
                midColumn)));
        }
        else
        {
            // matrix[midRow][midColumn] > target
            return ((searchSubMatrixRecursive(
                matrix,
                target,
                startRow,
                midRow - 1,
                startColumn,
                midColumn - 1)) ||
                (searchSubMatrixRecursive(
                matrix,
                target,
                startRow,
                midRow - 1,
                midColumn,
                endColumn)) ||
                (searchSubMatrixRecursive(
                matrix,
                target,
                midRow,
                endRow,
                startColumn,
                midColumn - 1)));
        }
    }

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

        return searchSubMatrixRecursive(
            matrix,
            target,
            0,
            cntRows - 1,
            0,
            cntColumns - 1);
    }
};