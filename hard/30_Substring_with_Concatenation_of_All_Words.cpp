using std::array;
using std::string;
using std::vector;

class Solution
{
    using StrView = std::string_view;

public:
    auto findSubstring(string s, vector<string> &words) -> vector<int>
    {
        auto res = vector<int>{};
        auto sv = StrView{s};
        auto wSize = size(words.front()), subSize = wSize * size(words);

        if (size(sv) < subSize) return res;

        auto counts = std::unordered_map<StrView, int>{};
        auto nOfNonZeros = 0u;
        auto push = [&nOfNonZeros, &counts](StrView sv)
        {
            auto &c = counts[sv];
            ++c;
            if (c == 1) { ++nOfNonZeros; }
            else if (c == 0) {
                --nOfNonZeros;
            }
        };
        auto pop = [&nOfNonZeros, &counts](StrView sv)
        {
            auto &c = counts[sv];
            --c;
            if (c == 0) { --nOfNonZeros; }
            else if (c == -1) {
                ++nOfNonZeros;
            }
        };

        for (auto const &w : words) push(w);

        for (auto i = size_t{0u}, end = std::min(wSize, size(sv) - subSize + 1); i < end; ++i) {
            auto posBeg = i, posEnd = i;
            for (auto endSub = posBeg + subSize; posEnd != endSub; posEnd += wSize) {
                pop(sv.substr(posEnd, wSize));
            }
            for (; posEnd <= size(sv); posBeg += wSize, posEnd += wSize) {
                if (nOfNonZeros == 0) res.push_back(posBeg);
                pop(sv.substr(posEnd, wSize));
                push(sv.substr(posBeg, wSize));
            }
            for (; posBeg != posEnd; posBeg += wSize) push(sv.substr(posBeg, wSize));
        }
        return res;
    }
};

