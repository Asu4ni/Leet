using std::vector;
using sz = std::size_t;

class Solution
{
public:
    int findLongestChain(vector<vector<int>> &pairs)
    {
        std::sort(begin(pairs), end(pairs),
                  [](auto const &vecA, auto const &vecB)
                  { return vecA[1] < vecB[1] || (vecA[1] == vecB[1] && vecA[0] > vecB[0]); });

        int res = 1;
        auto rightPrev = pairs.front()[1];
        for (auto const &vec : pairs) {
            auto &left = vec[0], &right = vec[1];
            if (left <= rightPrev) continue;
            ++res;
            rightPrev = right;
        }
        return res;
    }
};
