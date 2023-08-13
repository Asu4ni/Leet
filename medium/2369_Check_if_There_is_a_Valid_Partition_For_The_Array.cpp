using std::vector;
using sz = std::size_t;

class Solution
{
public:
    bool validPartition(vector<int> &nums)
    {
        auto const isSame2 = [&nums](sz idxLast) { return nums[idxLast] == nums[idxLast - 1]; };
        auto const isSame3 = [&nums](sz idxLast)
        { return nums[idxLast] == nums[idxLast - 1] && nums[idxLast - 1] == nums[idxLast - 2]; };
        auto const isIncr = [&nums](sz idxLast) {
            return nums[idxLast] == nums[idxLast - 1] + 1
                   && nums[idxLast - 1] == nums[idxLast - 2] + 1;
        };

        // 0: nums[0~2]? = {x, x, x}? || {x, x+1, x+2}?
        // 1: nums[0~1]? = {x, x}?
        // 2: nums[0~0]? = false
        auto dpRes = std::bitset<3>{};
        dpRes[1] = isSame2(1);
        if (size(nums) == 2) return dpRes[1];
        dpRes[0] = isSame3(2) || isIncr(2);
        sz idxDp = 0;

        for (sz idx = 3; idx < size(nums); ++idx) {
            idxDp = idxDp == 0 ? static_cast<sz>(2) : idxDp - 1;
            sz idxPrev2 = idxDp == 0 ? static_cast<sz>(2) : idxDp - 1;
            sz &idxPrev3 = idxDp;

            if (isSame2(idx) && dpRes[idxPrev2]) {
                dpRes[idxDp] = true;
                continue;
            }
            if ((isSame3(idx) || isIncr(idx)) && dpRes[idxPrev3]) {
                dpRes[idxDp] = true;
                continue;
            }
            dpRes[idxDp] = false;
        }

        return dpRes[idxDp];
    }
};
