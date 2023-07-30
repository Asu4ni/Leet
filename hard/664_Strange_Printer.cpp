using std::array;
using std::string;
using std::vector;
using sz = std::size_t;

class Solution
{
    static constexpr sz maxLen = 100u;

public:
    int strangePrinter(string s)
    {
        if (size(s) == 1) return 1;

        auto dpRes = array<int, ((maxLen - 1) + 1) * (maxLen - 1) / 2>{};

        auto const res = [&dpRes](sz idx, sz len) -> decltype(auto)
        {
            // ((maxLen - 1) + (maxLen - len + 2)) * (len - 2) / 2 + idx
            return dpRes[(maxLen * 2 - len + 1) * (len - 2) / 2 + idx];
        };
        auto const getRes = [&res](sz idx, sz len)
        {
            if (len < 2) return static_cast<int>(len);
            return res(idx, len);
        };

        for (sz len = 2u; len <= size(s); ++len) {
            for (sz idx = 0u, last = size(s) - len; idx <= last; ++idx) {
                auto &cur = res(idx, len);
                cur = std::numeric_limits<int>::max();
                for (sz lenFr = 1; lenFr < len; ++lenFr) {
                    sz const mid = idx + lenFr;
                    cur = std::min(s[idx] == s[mid]
                                           ? getRes(idx, lenFr) + getRes(mid + 1, len - lenFr - 1)
                                           : getRes(idx, lenFr) + getRes(mid, len - lenFr),
                                   cur);
                }
            }
        }

        return res(0u, size(s));
    }
};
