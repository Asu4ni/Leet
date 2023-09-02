using std::array;
using std::string;
using std::string_view;
using std::vector;
using sz = std::size_t;

class Solution
{
    using Idx = std::uint8_t;
    static constexpr Idx maxLen = 50;
    static constexpr Idx maxDict = 50;

    using Hash = std::uint64_t;
    static auto &updateHash(Hash &hash, char ch)
    {
        return hash = std::rotl(hash, 5) | static_cast<Hash>(ch - 'a' + 1);
    }
    static auto getHash(std::string_view strv)
    {
        Hash hash = 0;
        for (char ch : strv) updateHash(hash, ch);
        return hash;
    }

public:
    int minExtraChar(string s, vector<string> &dictionary)
    {
        auto const matchDict = [hashDict =
                                        [&dictionary]
                                {
                                    auto arr = array<Hash, maxDict>{};
                                    std::transform(begin(dictionary), end(dictionary), begin(arr),
                                                   [](auto const &str) { return getHash(str); });
                                    return arr;
                                }(),
                                n = size(dictionary)](Hash hash)
        {
            auto const beg = begin(hashDict), end = begin(hashDict) + n;
            return std::find(beg, end, hash) != end;
        };

        auto const nStr = size(s);
        auto dpRes = array<int, maxLen>{};
        auto hashStartingAt = array<Hash, maxLen>{};

        dpRes[0] = matchDict(updateHash(hashStartingAt[0], s[0])) ? 0 : 1;
        for (sz idxDp = 1; idxDp < nStr; ++idxDp) {
            dpRes[idxDp] = matchDict(updateHash(hashStartingAt[0], s[idxDp])) //
                                   ? 0
                                   : dpRes[idxDp - 1] + 1;
            for (sz idxStart = 1; idxStart <= idxDp; ++idxStart) {
                if (matchDict(updateHash(hashStartingAt[idxStart], s[idxDp]))) {
                    dpRes[idxDp] = std::min(dpRes[idxStart - 1], dpRes[idxDp]);
                }
            }
        }

        return dpRes[nStr - 1];
    }
};
