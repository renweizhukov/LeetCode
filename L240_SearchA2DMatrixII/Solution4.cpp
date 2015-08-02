class Solution
{
    // There are three directions for the one-dimensional searches used here: 
    // (1) RowFixed: search the elements along one row.
    // (2) ColumnFixed: search the elements along one column.
    // (3) Diagonal: search the elements along the diagonal from 
    //     top left corner to bottom right corner.
    enum struct SearchDirection { RowFixed, ColumnFixed, Diagonal };

    // Convert the one-dimensional index used in the binary search into the 
    // two-dimensional matrix index. Note that index and fixedIndex are 
    // not absolute values and they are relative values with respect to 
    // startRowIndex/startColumnIndex.
    pair<int, int> FromOneDimensionalIndexToTwoDimensionalIndexes(
        int startRowIndex,
        int startColumnIndex,
        int cntRows,
        int cntColumns,
        int index,              // one-dimensional index
        int fixedIndex,         // index of the fixed row/column
        SearchDirection direction)
    {
        pair<int, int> matrixIndexes(-1, -1);
        switch (direction)
        {
        case SearchDirection::RowFixed:
            matrixIndexes.first = startRowIndex + fixedIndex;
            matrixIndexes.second = startColumnIndex + index;
            break;

        case SearchDirection::ColumnFixed:
            matrixIndexes.first = startRowIndex + index;
            matrixIndexes.second = startColumnIndex + fixedIndex;
            break;

        case SearchDirection::Diagonal:
            // The "min" operation is to handle the non-square matrix. After 
            // the diagonal reaches the last row/column, it will continue along 
            // the last row/column towards the bottom right element.
            matrixIndexes.first = startRowIndex + min(cntRows - 1, index);
            matrixIndexes.second = startColumnIndex + min(cntColumns - 1, index);
            break;

        default:
            break;
        }

        return matrixIndexes;
    }

    // Standard bineary search along three different directions: 
    // RowFixed, ColumnFixed, and Diagonal.
    bool binarySearch(
        vector<vector<int>>& matrix,
        int startRowIndex,    // index of start row of the search submatrix
        int startColumnIndex, // index of start column of the search submatrix
        int cntRows,          // count of rows of the search submatrix
        int cntColumns,       // count of columns of the search submatrix
        int target,
        int start,            // one-dimensional start index of the binary search 
        int end,              // one-dimensional end index of the binary search
        int fixedIndex,       // index of the fixed row/column for RowFixed/ColumnFixed
        SearchDirection direction,
        int &firstLarger)     // one-dimensional index of the first element which 
        // is larger than target
    {
        firstLarger = -1;

        // Convert start and end into two-dimensional matrix indexes.
        pair<int, int> startIndexes = FromOneDimensionalIndexToTwoDimensionalIndexes(
            startRowIndex, startColumnIndex, cntRows, cntColumns, start, fixedIndex, direction);
        pair<int, int> endIndexes = FromOneDimensionalIndexToTwoDimensionalIndexes(
            startRowIndex, startColumnIndex, cntRows, cntColumns, end, fixedIndex, direction);

        // target is out of the range, so return false immediately.
        if ((target < matrix[startIndexes.first][startIndexes.second]) ||
            (target > matrix[endIndexes.first][endIndexes.second]))
        {
            return false;
        }

        while (start < end)
        {
            if ((target == matrix[startIndexes.first][startIndexes.second]) ||
                (target == matrix[endIndexes.first][endIndexes.second]))
            {
                return true;
            }

            int mid = (start + end) / 2;
            // Convert the one-dimensional index "mid" into a two-dimensional matrix index.
            pair<int, int> midIndexes = FromOneDimensionalIndexToTwoDimensionalIndexes(
                startRowIndex, startColumnIndex, cntRows, cntColumns, mid, fixedIndex, direction);
            if (target == matrix[midIndexes.first][midIndexes.second])
            {
                return true;
            }
            else if (target < matrix[midIndexes.first][midIndexes.second])
            {
                // target is in the first half. Note that we don't set "end" to "mid - 1" 
                // because we want to make sure that target is always smaller than end.
                end = mid;
                endIndexes = midIndexes;
            }
            else
            {
                // target > matrix[midIndexes.first][midIndexes.second]
                // target is in the second half.
                start = mid + 1;
                startIndexes = FromOneDimensionalIndexToTwoDimensionalIndexes(
                    startRowIndex, startColumnIndex, cntRows, cntColumns, start, fixedIndex, direction);
            }
        }

        firstLarger = end;
        return (target == matrix[endIndexes.first][endIndexes.second]);
    }

    bool searchSubMatrixRecursive(
        vector<vector<int>>& matrix,
        int startRowIndex,     // index of start row of the search submatrix
        int startColumnIndex,  // index of start column of the search submatrix
        int cntRows,           // count of rows of the search submatrix
        int cntColumns,        // count of columns of the search submatrix
        int target)
    {
        // firstLarger is the one-dimensional index of the first element which is  
        // larger than target during the binary search.
        int firstLarger = -1;

        if (cntRows == 1)
        {
            // The submatrix has only one row, so just do the binary search 
            // for target in that row.
            return binarySearch(
                matrix,
                startRowIndex,
                startColumnIndex,
                1,
                cntColumns,
                target,
                0,
                cntColumns - 1,
                0,
                SearchDirection::RowFixed,
                firstLarger);
        }

        if (cntColumns == 1)
        {
            // The submatrix has only one column, so just do the binary search 
            // for target in that column.
            return binarySearch(
                matrix,
                startRowIndex,
                startColumnIndex,
                cntRows,
                1,
                target,
                0,
                cntRows - 1,
                0,
                SearchDirection::ColumnFixed,
                lowestLarger);
        }

        // Do the binary search along the diagonal. 
        if (binarySearch(
            matrix,
            startRowIndex,
            startColumnIndex,
            cntRows,
            cntColumns,
            target,
            0,
            max(cntRows, cntColumns) - 1,
            -1,
            SearchDirection::Diagonal,
            firstLarger))
        {
            return true;
        }

        if (firstLarger == -1)
        {
            // Since we can't find "firstLarger", target must not exist in matrix.
            return false;
        }

        // Convert the one-dimensional index "firstLarger" into the two-dimensional 
        // matrix index.
        pair<int, int> firstLargerIndexes = FromOneDimensionalIndexToTwoDimensionalIndexes(
            startRowIndex,
            startColumnIndex,
            cntRows,
            cntColumns,
            firstLarger,
            -1,
            SearchDirection::Diagonal);

        // If the "firstLarger" element is on the diagonal or the last column, 
        // target may be in the bottom left submatrix.
        if (firstLargerIndexes.first - startRowIndex >=
            firstLargerIndexes.second - startColumnIndex)
        {
            if (searchSubMatrixRecursive(
                matrix,
                firstLargerIndexes.first,
                startColumnIndex,
                cntRows - (firstLargerIndexes.first - startRowIndex),
                firstLargerIndexes.second - startColumnIndex,
                target))
            {
                return true;
            }
        }

        // If the "firstLarger" element is on the diagonal or the last row,
        // target may be in the top right submatrix.
        if (firstLargerIndexes.first - startRowIndex <=
            firstLargerIndexes.second - startColumnIndex)
        {
            if (searchSubMatrixRecursive(
                matrix,
                startRowIndex,
                firstLargerIndexes.second,
                firstLargerIndexes.first - startRowIndex,
                cntColumns - (firstLargerIndexes.second - startColumnIndex),
                target))
            {
                return true;
            }
        }

        return false;
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

        // Recursively search target in matrix.
        return searchSubMatrixRecursive(
            matrix,
            0,
            0,
            cntRows,
            cntColumns,
            target);
    }
};