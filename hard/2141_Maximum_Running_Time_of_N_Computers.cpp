using std::array;
using std::string;
using std::vector;
using sz = std::size_t;

class Solution
{
public:
    auto maxRunTime(int n, vector<int> &batteries) -> long long
    {
        if (n > size(batteries)) return 0LL;
        if (n == size(batteries)) return *std::min_element(begin(batteries), end(batteries));

        std::sort(begin(batteries), end(batteries), std::greater{});

        auto sum = std::accumulate(begin(batteries), end(batteries), 0LL);

        for (auto itBat = begin(batteries);; ++itBat, --n) {
            if (auto usedAvg = sum / static_cast<long long>(n);
                static_cast<long long>(*itBat) <= usedAvg)
                return usedAvg;
            sum -= *itBat;
        }
    }
};
