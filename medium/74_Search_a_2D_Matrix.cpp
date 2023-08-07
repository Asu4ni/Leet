using std::vector;
using sz = std::size_t;

class Solution
{
public:
    bool searchMatrix(vector<vector<int>> &matrix, int target)
    {
        auto itRow = std::lower_bound(begin(matrix), end(matrix), target,
                                      [](auto &row, int target) { return row.back() < target; });
        if (itRow == end(matrix)) return false;
        if (itRow->back() == target) return true;

        return target == *std::lower_bound(begin(*itRow), prev(end(*itRow)), target);
    }
};
