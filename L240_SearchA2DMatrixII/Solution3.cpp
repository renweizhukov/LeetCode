class Solution
{
    bool searchSubMatrixRecursive(
        vector<vector<int>> &matrix,
        int target,
        int startRow,    // index of start row for the search
        int endRow,      // index of end row for the search
        int startColumn, // index of start column for the search
        int endColumn)   // index of end column for the search
    {
        // The search submatrix is empty.
        if ((startRow > endRow) || (startColumn > endColumn))
        {
            return false;
        }

        // The search submatrix has only one element.
        if ((startRow == endRow) && (startColumn == endColumn))
        {
            return (matrix[startRow][startColumn] == target);
        }

        // The search submatrix has more than one element. 
        // Compare the "center" element with target. The 
        // "center" element partitions the matrix into four 
        // submatrixes.
        int midRow = (startRow + endRow) / 2;
        int midColumn = (startColumn + endColumn) / 2;
        if (matrix[midRow][midColumn] == target)
        {
            // We have found target.
            return true;
        }
        else if (matrix[midRow][midColumn] < target)
        {
            // Since matrix[midRow][midColumn] is the maximum 
            // of the top left submatrix, target can only be 
            // found in the other three submatrixes.
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
            // Since matrix[midRow][midColumn] is the minimum 
            // of the bottom right submatrix, target can only 
            // be found in the other three submatrixes.
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
            // The matrix has zero row.
            return false;
        }

        int cntColumns = matrix[0].size();
        if (cntColumns == 0)
        {
            // The matrix has zero column.
            return false;
        }

        // Recursively search target in the matrix.
        return searchSubMatrixRecursive(
            matrix,
            target,
            0,
            cntRows - 1,
            0,
            cntColumns - 1);
    }
};