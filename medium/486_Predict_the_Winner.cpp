using std::array;
using std::string;
using std::vector;
using sz = std::size_t;

class Solution
{
public:
    bool PredictTheWinner(vector<int> &nums)
    {
        // pairs of point of the first & second player
        // at pos i, it represets the result using nums range [i, i + k] (k is the round)
        auto dpResult = vector<std::pair<int, int>>(size(nums));

        // round 0, nums's length = 1
        for (sz i = 0; i < size(nums); ++i) dpResult[i].first = nums[i];

        for (sz k = 1; k < size(nums); ++k) {
            for (sz i = 0; i + k < size(nums); ++i) {
                auto resTakeFr = std::pair{nums[i] + dpResult[i + 1].second, dpResult[i + 1].first};
                auto resTakeBk = std::pair{nums[i + k] + dpResult[i].second, dpResult[i].first};

                if (resTakeFr.first != resTakeBk.first) {
                    dpResult[i] = resTakeFr.first > resTakeBk.first ? resTakeFr : resTakeBk;
                }
                else {
                    dpResult[i] = resTakeFr.second < resTakeBk.second ? resTakeFr : resTakeBk;
                }
            }
        }

        return dpResult[0].first >= dpResult[0].second;
    }
};
