using std::vector;
using sz = std::size_t;

class Solution
{
public:
    int minTaps(int n, vector<int> &ranges)
    {
        int res = 0;

        // for each r in ranges
        // r[31:16] - left bound
        // r[15:0] - right bound
        auto const getLf = [](int r) { return r >> 16; };
        auto const getRt = [](int r) { return r & ((1 << 16) - 1); };
        for (int i = 0; i <= n; ++i) ranges[i] = ((i - ranges[i]) << 16) | (i + ranges[i]);

        std::sort(begin(ranges), end(ranges),
                  [&getLf, &getRt](int ra, int rb) {
                      return getLf(ra) < getLf(rb)
                             || (getLf(ra) == getLf(rb) && getRt(ra) > getRt(rb));
                  });

        auto const findNextLf = [&n, &ranges, &getLf](int idxBeg)
        {
            int const origLf = getLf(ranges[idxBeg]);
            ++idxBeg;
            while (idxBeg <= n && getLf(ranges[idxBeg]) == origLf) ++idxBeg;
            return idxBeg;
        };

        int curEnd = 0;
        for (int idx = 0; idx <= n && curEnd < n && getLf(ranges[idx]) <= curEnd;) {
            int nxtEnd = curEnd;
            do {
                nxtEnd = std::max(getRt(ranges[idx]), nxtEnd);
                idx = findNextLf(idx);
            } while (idx <= n && getLf(ranges[idx]) <= curEnd);
            curEnd = nxtEnd;
            ++res;
        }

        if (curEnd < n) res = -1;
        return res;
    }
};
