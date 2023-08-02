using std::string;
using std::vector;
using sz = std::size_t;

class Solution
{
    template <typename It>
    bool next_permutation(It begin, It end)
    {
        using std::next;
        using std::prev;
        // assert(std::distance(begin, end) >= 2);

        for (auto itFirstSmaller = prev(end, 2);; --itFirstSmaller) {
            if (*itFirstSmaller < *next(itFirstSmaller)) {
                begin = itFirstSmaller;
                break;
            }
            if (itFirstSmaller == begin) {
                // if conforming to std, std::reverse(begin, end);
                return false;
            }
        }

        auto itClosestLarger = prev(end);
        while (*begin >= *itClosestLarger) --itClosestLarger;

        std::iter_swap(begin, itClosestLarger);
        std::reverse(next(begin), end);
        return true;
    }

public:
    auto permute(vector<int> &nums) -> vector<vector<int>>
    {
        auto res = vector<vector<int>>{};
        if (size(nums) == 1) {
            res.push_back(nums);
            return res;
        }

        std::sort(nums.begin(), nums.end());
        do res.push_back(nums);
        while (next_permutation(nums.begin(), nums.end()));
        // if using std, while (std::next_permutation(nums.begin(), nums.end()));
        return res;
    }
};
