using std::array;
using std::string;
using std::string_view;
using std::vector;
using sz = std::size_t;

class Solution
{
    static constexpr auto divisor = 1000000007LL;
    static constexpr int maxN = 100;

    // only for k < n/2
    auto getCombs(int n)
    {
        auto combs = array<int, maxN / 2 + 1>{};

        // n = 1
        combs[0] = 1;

        for (int _n = 2; _n <= n; ++_n) {
            auto combPreNPreK = 1LL;
            for (int k = 1, lastK = (_n - 1) / 2; k <= lastK; ++k) {
                combPreNPreK = std::exchange(
                        combs[k], (combPreNPreK + static_cast<long long>(combs[k])) % divisor);
            }
            if (_n % 2 == 0) combs[_n / 2] = combPreNPreK * 2LL % divisor;
        }

        return combs;
    }

public:
    int numMusicPlaylists(int n, int goal, int k)
    {
        /* =   C(n, n) * (n * (n-1) * ... * (n-k)^(goal-k)
         *   - C(n, n-1) * ((n-1) * (n-2) * ... * (n-1-k)^(goal-k)
         *   + C(n, n-2) * ((n-2) * (n-3) * ... * (n-2-k)^(goal-k)
         *   ...
         */

        auto combs = getCombs(n);

        auto res = 0LL;
        // product from n to (n-k+1)
        bool add = true;
        for (int combK = n, lastK = k + 1; combK >= lastK; --combK) {
            auto cur = static_cast<long long>(combK * 2 <= n ? combs[combK] : combs[n - combK]);

            int num = combK;
            for (auto lastNum = combK - k + 1; num >= lastNum; --num) {
                cur = (cur * static_cast<long long>(num)) % divisor;
            }
            for (int i = goal - k; i > 0; --i) cur = (cur * static_cast<long long>(num)) % divisor;

            if (add) {
                res += cur;
                if (res > divisor) res -= divisor;
            }
            else {
                res -= cur;
                if (res < 0) res += divisor;
            }
            add = !add;
        }

        return static_cast<int>(res);
    }
};
