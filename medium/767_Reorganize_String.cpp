using std::array;
using std::string;
using std::string_view;
using std::vector;
using sz = std::size_t;

class Solution
{
    static constexpr char charMin = 'a';
    static constexpr char charMax = 'z';

    struct CharInfo
    {
        char ch;
        std::uint16_t count;
    };
    static consteval auto getInitCharInfo()
    {
        auto charInfos = array<CharInfo, charMax - charMin + 1>{};
        for (char ch = charMin; ch <= charMax; ++ch) charInfos[ch - charMin].ch = ch;
        return charInfos;
    }

public:
    auto reorganizeString(string s) -> string
    {
        auto charInfos = getInitCharInfo();
        for (char ch : s) ++charInfos[ch - charMin].count;
        std::sort(begin(charInfos), end(charInfos),
                  [](auto const &info0, auto const &info1) { return info0.count > info1.count; });

        auto res = std::move(s);
        if (static_cast<sz>(charInfos[0].count) * 2 > size(res) + 1) {
            res.clear();
            return res;
        }

        auto itInfo = begin(charInfos);
        for (sz idx = 0; idx < size(res); idx += 2) {
            if (itInfo->count == 0) ++itInfo;
            --itInfo->count;
            res[idx] = itInfo->ch;
        }
        for (sz idx = 1; idx < size(res); idx += 2) {
            if (itInfo->count == 0) ++itInfo;
            --itInfo->count;
            res[idx] = itInfo->ch;
        }

        return res;
    }
};
