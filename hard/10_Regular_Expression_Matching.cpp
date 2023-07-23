using std::array;
using std::string;
using std::vector;

class Solution
{
    template <typename It>
    bool match(It begStr, It endStr, It begPat, It endPat)
    {
        if (begStr == endStr && begPat == endPat) return true;
        if (begStr == endStr && *begPat != '*' || begPat == endPat) return false;

        if (*begPat == '*') {
            if (match(begStr, endStr, next(begPat, 2), endPat)) return true;
            for (auto it = begStr; it != endStr; ++it) {
                if (begPat[1] != '.' && *it != begPat[1]) break;
                if (match(next(it), endStr, next(begPat, 2), endPat)) return true;
            }
        }
        else if (*begPat == '.' || *begPat == *begStr) {
            return match(next(begStr), endStr, next(begPat), endPat);
        }
        return false;
    }

public:
    bool isMatch(string s, string p) { return match(rbegin(s), rend(s), rbegin(p), rend(p)); }
};

