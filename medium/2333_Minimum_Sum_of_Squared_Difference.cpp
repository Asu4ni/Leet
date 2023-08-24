using std::vector;
using sz = std::size_t;

class Solution
{
public:
    auto minSumSquareDiff(vector<int> &nums1, vector<int> &nums2, int k1, int k2) -> long long
    {
        auto res = 0LL;
        auto nOfChange = static_cast<long long>(k1) + k2;

        auto &diffs = nums1;
        auto sumOfDiff = 0LL;
        for (sz idx = 0; idx < size(nums1); ++idx) {
            diffs[idx] = std::abs(nums1[idx] - nums2[idx]);
            sumOfDiff += static_cast<long long>(diffs[idx]);
        }
        if (sumOfDiff <= nOfChange) return res;
        sumOfDiff -= nOfChange;

        std::sort(begin(diffs), end(diffs));

        auto prev = diffs[0] - diffs[0];
        for (sz idx = 0, width = size(diffs); idx < size(diffs); ++idx, --width) {
            auto blockSize
                    = static_cast<long long>(diffs[idx] - prev) * static_cast<long long>(width);
            if (sumOfDiff <= blockSize) {
                auto [height, rem] = std::lldiv(sumOfDiff, width);
                height += prev;
                res += height * height * (static_cast<long long>(width) - rem);
                res += (height + 1) * (height + 1) * rem;
                break;
            }
            sumOfDiff -= blockSize;

            res += static_cast<long long>(diffs[idx]) * diffs[idx];
            prev = diffs[idx];
        }

        return res;
    }
};
