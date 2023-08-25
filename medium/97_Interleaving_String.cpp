using std::string;
using std::string_view;
using std::vector;
using sz = std::size_t;

class Solution
{
    static constexpr sz maxLen = 100;

public:
    bool isInterleave(string s1, string s2, string s3)
    {
        auto len1 = size(s1), len2 = size(s2);
        auto const len3 = size(s3);
        if (len1 + len2 != len3) return false;
        if (len3 == 0) return true;
        if (len1 == 0) return s2 == s3;
        if (len2 == 0) return s1 == s3;

        if (len1 > len2) {
            s1.swap(s2);
            std::swap(len1, len2);
        }

        // for each round i (0 <= i <= len3) for s3[0,i);
        // dpRes[x] is true if isInterleave(s1[0,x), s2[0,i-x), s3[0,i))
        auto dpRes = std::bitset<maxLen + 1>{1}; // isInterleave(s1[0,0), s2[0,0), s3[0,0))

        for (sz i = 1; i <= len1; ++i) {
            dpRes.set(i, dpRes.test(i - 1) && s1[i - 1] == s3[i - 1]);
            for (sz x = i - 1; x > 0; --x) {
                dpRes.set(x, (dpRes.test(x - 1) && s1[x - 1] == s3[i - 1])
                                     || (dpRes.test(x) && s2[i - x - 1] == s3[i - 1]));
            }
            dpRes.set(0, dpRes.test(0) && s2[i - 1] == s3[i - 1]);

            if (dpRes.none()) return false;
        }
        for (sz i = len1 + 1; i <= len2; ++i) {
            for (sz x = len1; x > 0; --x) {
                dpRes.set(x, (dpRes.test(x - 1) && s1[x - 1] == s3[i - 1])
                                     || (dpRes.test(x) && s2[i - x - 1] == s3[i - 1]));
            }
            dpRes.set(0, dpRes.test(0) && s2[i - 1] == s3[i - 1]);

            if (dpRes.none()) return false;
        }
        for (sz i = len2 + 1; i <= len3; ++i) {
            sz const xMin = i - len2;
            for (sz x = len1; x >= xMin; --x) {
                dpRes.set(x, (dpRes.test(x - 1) && s1[x - 1] == s3[i - 1])
                                     || (dpRes.test(x) && s2[i - x - 1] == s3[i - 1]));
            }
            dpRes.reset(xMin - 1);

            if (dpRes.none()) return false;
        }

        return true;
    }
};
