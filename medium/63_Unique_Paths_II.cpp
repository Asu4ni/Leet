
using std::vector;
using sz = std::size_t;

class Solution
{
public:
    int uniquePathsWithObstacles(vector<vector<int>> &grid)
    {
        if (grid[0][0] == 1) return 0;

        grid[0][0] = 1;

        { // col = 0
            sz idxRow = 1;
            for (; idxRow < size(grid) && grid[idxRow][0] == 0; ++idxRow) grid[idxRow][0] = 1;
            for (; idxRow < size(grid); ++idxRow) grid[idxRow][0] = 0;
        }

        { // row = 0
            sz idxCol = 1;
            for (; idxCol < size(grid[0]) && grid[0][idxCol] == 0; ++idxCol) grid[0][idxCol] = 1;
            for (; idxCol < size(grid[0]); ++idxCol) grid[0][idxCol] = 0;
        }

        for (sz idxRow = 1; idxRow < size(grid); ++idxRow) {
            for (sz idxCol = 1; idxCol < size(grid[0]); ++idxCol) {
                grid[idxRow][idxCol]
                        = grid[idxRow][idxCol] == 1
                                  ? 0
                                  : grid[idxRow - 1][idxCol] + grid[idxRow][idxCol - 1];
            }
        }

        return grid.back().back();
    }
};
