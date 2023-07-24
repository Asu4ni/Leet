using std::array;
using std::string;
using std::vector;

class Solution
{
public:
    auto myPow(double x, int n) -> double
    {
        double res = 1.;
        if (n == 0) return res;

        x = n < 0 ? 1. / x : x;
        for (auto p = n < 0 ? static_cast<unsigned>(std::llabs(n)) : static_cast<unsigned>(n);
             p != 0; p >>= 1) {
            if ((p & 1u) == 1u) res *= x;
            x *= x;
        }
        return res;
    }
};

