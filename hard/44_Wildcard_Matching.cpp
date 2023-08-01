using std::string;
using std::vector;
using sz = std::size_t;

class Solution
{
public:
    bool isMatch(string s, string p)
    {
        sz patPos = 0u, astPos = string::npos;
        sz lastPos;
        for (sz strPos = 0u; strPos < size(s);) {
            if (patPos < size(p) && p[patPos] == '*') {
                lastPos = strPos;
                astPos = patPos;
                ++patPos;
            }
            else if (patPos < size(p) && (p[patPos] == '?' || s[strPos] == p[patPos])) {
                ++strPos;
                ++patPos;
            }
            else if (astPos != string::npos) {
                strPos = ++lastPos;
                patPos = astPos + 1;
            }
            else {
                return false;
            }
        }
        return std::all_of(next(begin(p), patPos), end(p), [](char ch) { return ch == '*'; });
    }
};
