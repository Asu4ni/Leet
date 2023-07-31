using std::array;
using std::string;
using std::vector;
using sz = std::size_t;

class Solution
{
    static constexpr sz maxLen = 1000u;

public:
    int minimumDeleteSum(string s1, string s2)
    {
        // dp[i][j]: cost of s1.substr(0, i) & s2.substr(0, j)
        //  for round s from 0 to s1.size()-1,
        //      prevDpRow[t]: dp[s][t]
        //      curDpRow[t]: dp[s+1][t]
        auto dpRow0 = array<int, maxLen + 1>{};
        auto dpRow1 = array<int, maxLen + 1>{};

        // prepare dp[0]
        {
            auto &curDpRow = dpRow0;
            curDpRow[0] = 0;
            for (sz t = 0; t < size(s2); ++t) {
                curDpRow[t + 1] = curDpRow[t] + static_cast<int>(s2[t]);
            }
        }

        for (sz s = 0; s < size(s1); ++s) {
            auto [curDpRow, prevDpRow]
                    = s % 2 == 1 ? std::tie(dpRow0, dpRow1) : std::tie(dpRow1, dpRow0);

            curDpRow[0] = prevDpRow[0] + s1[s];
            for (sz t = 0; t < size(s2); ++t) {
                curDpRow[t + 1] = std::min(static_cast<int>(s1[s]) + prevDpRow[t + 1],
                                           static_cast<int>(s2[t]) + curDpRow[t]);
                if (s1[s] == s2[t]) curDpRow[t + 1] = std::min(prevDpRow[t], curDpRow[t + 1]);
            }
        }

        return (size(s1) % 2 == 0 ? dpRow0 : dpRow1)[size(s2)];
    }
};
