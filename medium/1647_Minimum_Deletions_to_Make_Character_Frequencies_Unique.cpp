using std::array, std::vector;
using std::begin, std::end, std::next, std::size;
using std::string, std::string_view;
using sz = std::size_t;

class Solution
{
    static constexpr char chMin = 'a', chMax = 'z';

public:
    int minDeletions(string s)
    {
        auto counts = array<int, chMax - chMin + 1>{};
        for (char ch : s) ++counts[ch - chMin];
        std::sort(begin(counts), end(counts), std::greater{});

        int res = 0;
        auto itStackEnd = begin(counts); // stack: storing pending count
        int prevCount = counts[0] + 1;
        for (int count : counts) {
            if (count == 0) break;
            if (count == prevCount) {
                *itStackEnd = count;
                ++itStackEnd;
            }
            else {
                while (itStackEnd != begin(counts) && prevCount - count > 1) {
                    --itStackEnd;
                    --prevCount;
                    res += *itStackEnd - prevCount;
                }
            }

            prevCount = count;
        }

        while (itStackEnd != begin(counts)) {
            --itStackEnd;
            if (prevCount > 0) --prevCount;
            res += *itStackEnd - prevCount;
        }

        return res;
    }
};
