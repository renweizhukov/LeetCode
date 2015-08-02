class Solution
{
    enum struct SearchDirection { RowFixed, ColumnFixed, Diagonal };
    pair<int, int> FromOneDimensionalIndexToTwoDimensionalIndexes(
        int startRowIndex,
        int startColumnIndex,
        int cntRows,
        int cntColumns,
        int index,
        int fixedIndex,
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
            matrixIndexes.first = startRowIndex + min(cntRows - 1, index);
            matrixIndexes.second = startColumnIndex + min(cntColumns - 1, index);
            break;

        default:
            break;
        }

        return matrixIndexes;
    }

    bool binarySearch(
        vector<vector<int>>& matrix,
        int startRowIndex,
        int startColumnIndex,
        int cntRows,
        int cntColumns,
        int target,
        int start,
        int end,
        int fixedIndex,
        SearchDirection direction,
        int &lowestLarger)
    {
        lowestLarger = -1;

        pair<int, int> startIndexes = FromOneDimensionalIndexToTwoDimensionalIndexes(
            startRowIndex, startColumnIndex, cntRows, cntColumns, start, fixedIndex, direction);
        pair<int, int> endIndexes = FromOneDimensionalIndexToTwoDimensionalIndexes(
            startRowIndex, startColumnIndex, cntRows, cntColumns, end, fixedIndex, direction);

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
            pair<int, int> midIndexes = FromOneDimensionalIndexToTwoDimensionalIndexes(
                startRowIndex, startColumnIndex, cntRows, cntColumns, mid, fixedIndex, direction);
            if (target == matrix[midIndexes.first][midIndexes.second])
            {
                return true;
            }
            else if (target < matrix[midIndexes.first][midIndexes.second])
            {
                end = mid;
                endIndexes = midIndexes;
            }
            else
            {
                // target > matrix[midIndexes.first][midIndexes.second]
                start = mid + 1;
                startIndexes = FromOneDimensionalIndexToTwoDimensionalIndexes(
                    startRowIndex, startColumnIndex, cntRows, cntColumns, start, fixedIndex, direction);
            }
        }

        lowestLarger = end;
        return (target == matrix[endIndexes.first][endIndexes.second]);
    }

    bool searchMatrix(
        vector<vector<int>>& matrix,
        int startRowIndex,
        int startColumnIndex,
        int cntRows,
        int cntColumns,
        int target)
    {
        int lowestLarger = -1;

        if (cntRows == 1)
        {
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
                lowestLarger);
        }

        if (cntColumns == 1)
        {
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
            lowestLarger))
        {
            return true;
        }

        if (lowestLarger == -1)
        {
            return false;
        }

        pair<int, int> lowestLargerIndexes = FromOneDimensionalIndexToTwoDimensionalIndexes(
            startRowIndex,
            startColumnIndex,
            cntRows,
            cntColumns,
            lowestLarger,
            -1,
            SearchDirection::Diagonal);
        if (lowestLargerIndexes.first - startRowIndex >=
            lowestLargerIndexes.second - startColumnIndex)
        {
            if (searchMatrix(
                matrix,
                lowestLargerIndexes.first,
                startColumnIndex,
                cntRows - (lowestLargerIndexes.first - startRowIndex),
                lowestLargerIndexes.second - startColumnIndex,
                target))
            {
                return true;
            }
        }

        if (lowestLargerIndexes.first - startRowIndex <=
            lowestLargerIndexes.second - startColumnIndex)
        {
            if (searchMatrix(
                matrix,
                startRowIndex,
                lowestLargerIndexes.second,
                lowestLargerIndexes.first - startRowIndex,
                cntColumns - (lowestLargerIndexes.second - startColumnIndex),
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
            return false;
        }

        int cntColumns = matrix[0].size();
        if (cntColumns == 0)
        {
            return false;
        }

        return searchMatrix(
            matrix,
            0,
            0,
            cntRows,
            cntColumns,
            target);
    }
};