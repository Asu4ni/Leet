using std::array, std::vector;
using std::begin, std::end, std::next, std::size;
using std::string, std::string_view;
using sz = std::size_t;

class Solution
{
    using GroupId = std::int16_t; // -1: no idx yet
    static constexpr sz sizeMax = 500;

public:
    auto groupThePeople(vector<int> &groupSizes) -> vector<vector<int>>
    {
        auto res = vector<vector<int>>{};

        auto groupIds = array<GroupId, sizeMax>{};
        std::fill(begin(groupIds), next(begin(groupIds), size(groupSizes)), -1);

        for (int idx = 0; idx < static_cast<int>(size(groupSizes)); ++idx) {
            auto &gid = groupIds[groupSizes[idx] - 1];
            if (gid == -1 || size(res[gid]) == static_cast<sz>(groupSizes[idx])) {
                res.emplace_back();
                gid = static_cast<GroupId>(size(res) - 1);
            }
            res[gid].push_back(idx);
        }

        return res;
    }
};
