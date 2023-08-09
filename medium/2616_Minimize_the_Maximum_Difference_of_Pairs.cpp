using std::vector;
using sz = std::size_t;

class Solution
{
public:
    template <typename It>
    sz maxNOfNonAdjacentNumsNotGreaterThan(It itBeg, It itEnd, int value)
    {
        sz count = 0;
        for (; itBeg != itEnd; ++itBeg) {
            if (*itBeg > value) continue;

            ++count;
            if (++itBeg == itEnd) break;
        }
        return count;
    }

    int minimizeMax(vector<int> &nums, int p)
    {
        if (p == 0) return 0;

        std::sort(begin(nums), end(nums));
        std::adjacent_difference(begin(nums), end(nums), begin(nums));

        auto const begDiff = next(begin(nums)), endDiff = end(nums);

        auto [ansMin, ansMax] = [&begDiff, &endDiff]()
        {
            auto [itMinDiff, itMaxDiff] = std::minmax_element(begDiff, endDiff);
            return std::tuple{*itMinDiff, *itMaxDiff};
        }();
        while (ansMin != ansMax) {
            auto ansMid = (ansMin + ansMax) / 2;

            if (maxNOfNonAdjacentNumsNotGreaterThan(begDiff, endDiff, ansMid)
                >= static_cast<sz>(p)) {
                ansMax = ansMid;
            }
            else {
                ansMin = ansMid + 1;
            }
        }

        return ansMin;
    }
};
