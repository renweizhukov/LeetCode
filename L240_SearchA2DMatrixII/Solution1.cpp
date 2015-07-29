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

        // Compare the top right element with target. 
        // (1) If they are equal, we have found the target. 
        // (2) If the top right element is smaller than target, 
        //     we can skip all the elements in the same row 
        //     since they can't be larger than the top right element.
        // (3) If the top right element is larger than target,
        //     we can skip all the elements in the same column
        //     since they can't be smaller than the top right element.
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