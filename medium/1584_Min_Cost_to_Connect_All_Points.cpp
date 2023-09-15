using std::array, std::vector;
using std::begin, std::end, std::next, std::size;
using std::string, std::string_view;
using sz = std::size_t;

class Solution
{
    using Idx = std::uint16_t;
    static constexpr Idx maxPoints = 1000;

public:
    int minCostConnectPoints(vector<vector<int>> &points)
    {
        int cost = 0;
        Idx const nPoints = size(points);

        auto distsToComp = std::array<int, maxPoints>{};
        std::fill(begin(distsToComp), next(begin(distsToComp), nPoints),
                  std::numeric_limits<int>::max());

        auto const dist = [&points](Idx idxA, Idx idxB)
        {
            using std::abs;
            return abs(points[idxA][0] - points[idxB][0]) + abs(points[idxA][1] - points[idxB][1]);
        };

        Idx curIdx = 0;
        for (Idx szComp = 1; szComp < nPoints; ++szComp) {
            distsToComp[curIdx] = 0;
            Idx nxtIdx = curIdx;
            int nxtCost = std::numeric_limits<int>::max();
            for (Idx idxUpdate = 0; idxUpdate < nPoints; ++idxUpdate) {
                if (distsToComp[idxUpdate] == 0) continue;
                distsToComp[idxUpdate] = std::min(dist(curIdx, idxUpdate), distsToComp[idxUpdate]);
                if (distsToComp[idxUpdate] < nxtCost) {
                    nxtIdx = idxUpdate;
                    nxtCost = distsToComp[idxUpdate];
                }
            }
            cost += nxtCost;
            curIdx = nxtIdx;
        }

        return cost;
    }
};
