using std::vector;
using sz = std::size_t;

class Solution
{
    static constexpr sz maxN = 100;
    using Idx = std::uint8_t;
    using Count = std::uint8_t;
    struct CityInfo
    {
        Idx idx;
        Count nOfNeigh;
    };

public:
    int maximalNetworkRank(int n, vector<vector<int>> &roads)
    {
        auto cityInfos = vector<CityInfo>(static_cast<sz>(n));
        for (sz idx = 0; idx < static_cast<sz>(n); ++idx) { cityInfos[idx].idx = idx; }

        auto isNeigh = [adjMatrix = std::bitset<maxN *(maxN - 1) / 2>{}](Idx idxCityA,
                                                                         Idx idxCityB) mutable
        {
            auto [idx1, idx2] = idxCityA < idxCityB ? std::tie(idxCityA, idxCityB)
                                                    : std::tie(idxCityB, idxCityA);
            return adjMatrix[idx2 * (idx2 - 1) / 2 + idx1];
        };

        for (auto &pair : roads) {
            ++cityInfos[pair[0]].nOfNeigh;
            ++cityInfos[pair[1]].nOfNeigh;
            isNeigh(pair[0], pair[1]) = true;
        }
        std::sort(begin(cityInfos), end(cityInfos),
                  [](auto const &a, auto const &b) { return a.nOfNeigh > b.nOfNeigh; });

        auto const nOfNeighMax = cityInfos[0].nOfNeigh;
        auto const itNeighMaxEnd = std::find_if(next(begin(cityInfos)), end(cityInfos),
                                                [&nOfNeighMax](auto const &info)
                                                { return info.nOfNeigh < nOfNeighMax; });
        if (distance(begin(cityInfos), itNeighMaxEnd) > 1) {
            // find if there are two cities among NeighMax that aren't neighbors
            for (auto it1 = begin(cityInfos); it1 != itNeighMaxEnd; ++it1) {
                for (auto it2 = next(it1); it2 != itNeighMaxEnd; ++it2) {
                    if (!isNeigh(it1->idx, it2->idx)) return static_cast<int>(nOfNeighMax) * 2;
                }
            }
            return static_cast<int>(nOfNeighMax) * 2 - 1;
        }

        auto const nOfNeighR2 = cityInfos[1].nOfNeigh;
        auto const itNeighR2End = std::find_if(next(begin(cityInfos), 2), end(cityInfos),
                                               [&nOfNeighR2](auto const &info)
                                               { return info.nOfNeigh < nOfNeighR2; });
        for (auto it = next(begin(cityInfos)); it != itNeighR2End; ++it) {
            if (!isNeigh(cityInfos[0].idx, it->idx)) {
                return static_cast<int>(nOfNeighMax) + static_cast<int>(nOfNeighR2);
            }
        }
        return static_cast<int>(nOfNeighMax) + static_cast<int>(nOfNeighR2) - 1;
    }
};
