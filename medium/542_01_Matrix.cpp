using std::vector;
using sz = std::size_t;

class Solution
{
    struct Pos
    {
        sz row, col;
        Pos(sz row, sz col) : row{row}, col{col} {}
    };

public:
    auto updateMatrix(vector<vector<int>> &mat) -> vector<vector<int>>
    {
        auto res = std::move(mat);
        auto const szRow = size(res), szCol = size(res[0]);

        auto curQueue = vector<Pos>{}, nxtQueue = curQueue;

        for (sz row = 0; row < szRow; ++row) {
            for (sz col = 0; col < szCol; ++col) {
                if (res[row][col] == 0) continue;

                if ((row > 0 && res[row - 1][col] == 0) // next to '0'
                    || (col > 0 && res[row][col - 1] == 0)
                    || (row < szRow - 1 && res[row + 1][col] == 0)
                    || (col < szCol - 1 && res[row][col + 1] == 0)) {
                    curQueue.emplace_back(row, col);
                }
                else {
                    res[row][col] = -1;
                }
            }
        }

        auto const visit = [&res, &nxtQueue](sz row, sz col, int dist)
        {
            if (res[row][col] != -1) return;
            res[row][col] = dist;
            nxtQueue.emplace_back(row, col);
        };
        for (; !curQueue.empty(); curQueue.swap(nxtQueue), nxtQueue.clear()) {
            for (auto [row, col] : curQueue) {
                int dist = res[row][col] + 1;

                if (row > 0) visit(row - 1, col, dist);
                if (col > 0) visit(row, col - 1, dist);
                if (row < szRow - 1) visit(row + 1, col, dist);
                if (col < szCol - 1) visit(row, col + 1, dist);
            }
        }

        return res;
    }
};
