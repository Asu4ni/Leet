using std::array;
using std::string;
using std::string_view;
using std::vector;
using sz = std::size_t;

class Solution
{
public:
    auto fullJustify(vector<string> &words, int maxWidth) -> vector<string>
    {
        auto res = vector<string>{};

        auto itWordsBeg = begin(words);
        sz len = size(words[0]);
        for (auto it = next(begin(words)); it != end(words); ++it) {
            if (sz len_ = len + size(*it) + 1; len_ <= static_cast<sz>(maxWidth)) {
                len = len_;
                continue;
            }

            auto &line = res.emplace_back();
            auto const nWords = distance(itWordsBeg, it);
            auto const nSpaces = static_cast<sz>(maxWidth) - len + nWords - 1;
            if (nWords == 1) {
                line.append(*itWordsBeg);
                line.append(nSpaces, ' ');
            }
            else {
                auto [nAvgSpace, nExtraSpace] = std::div(nSpaces, nWords - 1);
                for (sz i = 0; i < nWords - 1; ++i, ++itWordsBeg) {
                    line.append(*itWordsBeg);
                    line.append(nAvgSpace, ' ');
                    if (--nExtraSpace >= 0) line.push_back(' ');
                }
                line.append(*itWordsBeg);
            }
            len = size(*it);
            ++itWordsBeg;
        }
        auto &line = res.emplace_back();
        for (; itWordsBeg != end(words); ++itWordsBeg) {
            line.append(*itWordsBeg);
            line.push_back(' ');
        }
        line.resize(maxWidth, ' ');

        return res;
    }
};
