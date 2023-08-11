using std::array;
using std::string;
using std::string_view;
using std::vector;
using sz = std::size_t;

class Solution
{
    static constexpr int maxAmount = 5000;

public:
    int change(int amount, vector<int> &coins)
    {
        auto combOfAmount = array<int, maxAmount + 1>{};
        combOfAmount[0] = 1;

        std::sort(begin(coins), end(coins));
        for (int coin : coins) {
            if (coin > amount) break;
            for (int idxAmount = coin, endAmount = amount - coin; idxAmount <= endAmount;
                 ++idxAmount) {
                combOfAmount[idxAmount] += combOfAmount[idxAmount - coin];
            }
            combOfAmount[amount] += combOfAmount[amount - coin];
        }

        return combOfAmount[amount];
    }
};
