using std::array;
using std::string;
using std::vector;
using sz = std::size_t;
using namespace std::string_view_literals;

class Solution
{
    static constexpr auto lettersOfDigits
            = array{"abc"sv, "def"sv, "ghi"sv, "jkl"sv, "mno"sv, "pqrs"sv, "tuv"sv, "wxyz"sv};

public:
    auto letterCombinations(string digits) -> vector<string>
    {
        auto res = vector<string>{};
        if (digits.empty()) return res;

        res.push_back("");
        for (char d : digits) {
            auto const letters = lettersOfDigits[d - '2'];
            auto const prevResSize = size(res);

            res.reserve(prevResSize * size(letters));
            std::copy_n(begin(res), prevResSize * (size(letters) - 1), back_inserter(res));

            auto itRes = begin(res);
            for (char c : letters) {
                itRes = for_each_n(itRes, prevResSize, [c](auto &s) { s.push_back(c); });
            }
        }
        return res;
    }
};
