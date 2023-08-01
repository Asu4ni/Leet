using std::array;
using std::string;
using std::vector;
using sz = std::size_t;

class Solution
{
    void loop(sz num, sz kth, sz n, sz k, vector<vector<int>> &res, vector<int> &tmp)
    {
        if (kth == k) {
            res.push_back(tmp);
            return;
        }

        for (sz last = n - (k - kth) + 1; num <= last; ++num) {
            tmp[kth] = num;
            loop(num + 1, kth + 1, n, k, res, tmp);
        }
    }

public:
    auto combine(int n, int k) -> vector<vector<int>>
    {
        auto res = vector<vector<int>>{};
        auto tmp = vector<int>(k);
        loop(1, 0, n, k, res, tmp);
        return res;
    }
};
