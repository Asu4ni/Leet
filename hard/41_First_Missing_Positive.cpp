using std::array;
using std::string;
using std::vector;
using sz = std::size_t;

class Solution
{
public:
    int firstMissingPositive(vector<int> &nums)
    {
        // remove non-positive numbers
        nums.erase(remove_if(begin(nums), end(nums), [](int n) { return n <= 0; }), end(nums));

        // position i records if number i+1 exists (< 0)
        // = 0: empty
        // > 0: the number
        for (int i = 0; i < size(nums); ++i) {
            if (nums[i] <= 0) continue;

            int num = std::exchange(nums[i], 0);
            while (num >= 1 && num <= size(nums)) num = std::exchange(nums[num - 1], -1);
        }
        return 1 + distance(begin(nums), find(begin(nums), end(nums), 0));
    }
};

