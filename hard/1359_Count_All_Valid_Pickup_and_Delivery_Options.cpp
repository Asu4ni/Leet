class Solution
{
    static constexpr int mod = 1000000007;
public:
    int countOrders(int n)
    {
        int res = 1;
        // res = 2n! / 2^n
        for (; n > 0; --n) {
            // *= 2n * (2n - 1) / 2
            res = static_cast<int>(static_cast<std::int64_t>(res) * n * (2 * n - 1) % mod);
        }
        return res;
    }
};
