using std::array;
using std::string;
using std::string_view;
using std::vector;
using sz = std::size_t;

class Solution
{
    static constexpr auto nOfChars = static_cast<sz>(('Z' - 'A') + 1 + ('z' - 'a') + 1);
    static constexpr auto getIdx(char ch)
    {
        auto idx = static_cast<sz>(ch - 'A');
        if (idx > static_cast<sz>('Z' - 'A')) idx = static_cast<sz>(ch - 'a') + 26u;
        return idx;
    }

public:
    auto minWindow(string s, string t)-> string
    {
        auto counts = array<int, nOfChars>{};
        auto notOks = std::bitset<52>{};
        auto const push = [&counts, &notOks](char c)
        {
            auto idx = getIdx(c);
            if (counts[idx] == -1) notOks.reset(idx);
            ++counts[idx];
        };
        auto const pop = [&counts, &notOks](char c)
        {
            auto idx = getIdx(c);
            if (counts[idx] == 0) notOks.set(idx);
            --counts[idx];
        };

        for (char c : t) pop(c);

        auto minLen = std::numeric_limits<sz>::max();
        auto minBegIt = begin(s);
        auto minEndIt = begin(s);
        for (auto itBeg = begin(s), itEnd = itBeg; itEnd != end(s);) {
            for (; !(itEnd == end(s) || notOks.none()); ++itEnd) push(*itEnd);
            if (!notOks.none()) break;

            for (; notOks.none(); ++itBeg) pop(*itBeg);

            if (auto len = static_cast<sz>(distance(prev(itBeg), itEnd)); len < minLen) {
                minLen = len;
                minBegIt = prev(itBeg);
                minEndIt = itEnd;
            }
        }

        return string{minBegIt, minEndIt};
    }
};
