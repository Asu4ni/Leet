using std::array, std::vector;
using std::begin, std::end, std::next, std::size;
using std::string, std::string_view;
using sz = std::size_t;

class Solution
{
    using Idx = std::uint8_t;
    static constexpr sz szMax = 100;

    struct Record
    {
        int effort;
        Idx row, col;
    };

public:
    int minimumEffortPath(vector<vector<int>> &heights)
    {
        Idx const szRow = size(heights), szCol = size(heights[0]);

        auto visitedOf = [set = std::bitset<szMax * szMax>{}, &szCol](Idx row, Idx col) mutable
        { return set[row * szCol + col]; };

        for (auto pq = std::priority_queue{[](Record const &a, Record const &b)
                                           { return a.effort > b.effort; },
                                           vector{Record{.effort = 0, .row = 0, .col = 0}}};
             ;) {
            auto [effort, row, col] = pq.top();
            if (row == szRow - 1 && col == szCol - 1) return effort;
            pq.pop();
            visitedOf(row, col) = true;

            auto const calc = [&](Idx nxtRow, Idx nxtCol)
            {
                if (visitedOf(nxtRow, nxtCol)) return;
                pq.push({.effort
                         = std::max(effort, std::abs(heights[row][col] - heights[nxtRow][nxtCol])),
                         .row = nxtRow,
                         .col = nxtCol});
            };
            if (row != 0) calc(static_cast<Idx>(row - 1), col);
            if (col != 0) calc(row, static_cast<Idx>(col - 1));
            if (row != static_cast<Idx>(szRow - 1)) calc(static_cast<Idx>(row + 1), col);
            if (col != static_cast<Idx>(szCol - 1)) calc(row, static_cast<Idx>(col + 1));
        }
    }
};
