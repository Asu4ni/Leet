using std::vector;
using sz = std::size_t;

class Solution
{
    static constexpr int noneVal = std::numeric_limits<int>::min();

public:
    int maxProfit(int k, vector<int> &prices)
    {
        if (size(prices) < 2 || k < 1) return 0;

        auto solds = vector<int>(k, noneVal);
        auto holdings = vector<int>(k, noneVal);

        holdings[0] = -prices[0];
        for (sz day = 1; day < size(prices); ++day) {
            for (auto nth = std::min(static_cast<sz>(k - 1), (day - 1) / 2); nth > 0; --nth) {
                solds[nth] = std::max(holdings[nth] + prices[day], solds[nth]);
                holdings[nth] = std::max(solds[nth - 1] - prices[day], holdings[nth]);
            }
            if (day < k * 2 && day % 2 == 0)
                holdings[day / 2] = std::max(holdings[day / 2], solds[day / 2 - 1] - prices[day]);

            solds[0] = std::max(solds[0], holdings[0] + prices[day]);
            holdings[0] = std::max(holdings[0], -prices[day]);
        }
        
        return std::max(0, *max_element(begin(solds), end(solds)));
    }
};
