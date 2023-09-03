class Solution
{
public:
    int uniquePaths(int m, int n)
    {
        int a = m + n - 2;
        int b = m < n ? m - 1 : n - 1;

        auto res = std::uint64_t{1};
        for (int i = 1; i <= b; ++i, --a) {
            res *= static_cast<decltype(res)>(a);
            res /= static_cast<decltype(res)>(i);
        }
        return static_cast<int>(res);
    }
};
