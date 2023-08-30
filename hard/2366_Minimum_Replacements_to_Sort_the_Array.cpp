using std::vector;
using sz = std::size_t;

class Solution
{
public:
    auto minimumReplacement(vector<int> &nums) -> long long
    {
        auto res = 0LL;

        auto prev = nums.back();
        for (sz idx = size(nums) - 2; idx < size(nums); --idx) {
            auto const &cur = nums[idx];
            if (cur <= prev) {
                prev = cur;
                continue;
            }

            auto const nOfParts = (cur - 1) / prev + 1;
            res += static_cast<long long>(nOfParts - 1);
            prev = cur / nOfParts;
        }
        return res;
    }
};
