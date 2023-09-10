using std::array;
using std::string;
using std::string_view;
using std::vector;
using sz = std::size_t;

class Solution
{
    static constexpr int targetMax = 1000;

public:
    int combinationSum4(vector<int> &nums, int target)
    {
        auto counts = array<std::uint32_t, targetMax + 1>{};
        counts[0] = 1;
        for (int i = 1; i <= target; ++i) {
            for (int const &n : nums) {
                if (i < n) continue;
                // overflow can be ignored
                counts[i] += counts[i - n];
            }
        }
        return static_cast<int>(counts[target]);
    }
};
