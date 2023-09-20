using std::array, std::vector;
using std::begin, std::end, std::next, std::size;
using std::string, std::string_view;
using sz = std::size_t;

class Solution
{
public:
    int minOperations(vector<int> &nums, int x)
    {
        int const targetSum = std::reduce(begin(nums), end(nums)) - x;
        if (targetSum == 0) return static_cast<int>(size(nums));
        if (targetSum < 0) return -1;

        int maxLen = 0;
        {
            int sum = 0;
            for (auto itBeg = begin(nums), itEnd = itBeg; itEnd != end(nums);) {
                do {
                    sum += *itEnd;
                    ++itEnd;
                } while (itEnd != end(nums) && sum < targetSum);
                if (sum < targetSum) break;

                while (sum > targetSum) {
                    sum -= *itBeg;
                    ++itBeg;
                }

                if (sum == targetSum) {
                    maxLen = std::max(static_cast<int>(std::distance(itBeg, itEnd)), maxLen);
                    sum -= *itBeg;
                    ++itBeg;
                }
            }
        }

        return maxLen == 0 ? -1 : static_cast<int>(size(nums)) - maxLen;
    }
};
