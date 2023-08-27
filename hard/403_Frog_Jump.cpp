using std::vector;
using sz = std::size_t;

class Solution
{
public:
    bool canCross(vector<int> &stones)
    {
        if (stones[1] != stones[0] + 1) return false;

        auto lastSteps = vector<vector<int>>(size(stones));
        lastSteps[1] = vector{1};

        // return 0 if pos is not found
        auto const findIdx = [begIt = begin(stones), endIt = end(stones)](int pos, auto itBegToFind)
        {
            auto const it = std::lower_bound(itBegToFind, endIt, pos);
            if (it != endIt && *it == pos) return distance(begIt, it);
            return distance(begIt, begIt);
        };

        for (sz idx = 1; idx < size(stones); ++idx) {
            int pos = stones[idx];
            std::sort(begin(lastSteps[idx]), end(lastSteps[idx]));
            int posCheckPrev = 0;
            for (int step : lastSteps[idx]) {
                int posCheck = pos + step;
                if (posCheck == posCheckPrev || posCheck - 1 > stones.back()) break;

                auto itBegToFind = next(begin(stones), idx + 1);
                if (posCheckPrev + 1 < posCheck) {
                    if (posCheckPrev + 2 < posCheck) {
                        auto idxFind = findIdx(posCheck - 1, itBegToFind);
                        if (idxFind > 0) lastSteps[idxFind].push_back(step - 1);
                    }
                    auto idxFind = findIdx(posCheck, itBegToFind);
                    if (idxFind > 0) lastSteps[idxFind].push_back(step);
                }

                auto idxFind = findIdx(posCheck + 1, itBegToFind);
                if (idxFind > 0) lastSteps[idxFind].push_back(step + 1);

                posCheckPrev = posCheck;
            }
        }

        return !lastSteps.back().empty();
    }
};
