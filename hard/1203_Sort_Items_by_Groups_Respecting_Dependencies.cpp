using std::vector;
using sz = std::size_t;

class Solution
{
    using Count = std::uint16_t;
    struct Group
    {
        struct Member
        {
            int idx;
            vector<int> afterMemberIds{};
            Count nInEdges = 0;
        };
        using Members = vector<Member>;

        std::variant<int, Members> idxOrMembers;
        vector<int> afterGroupIds{};
        Count nInEdges = 0;
        Group() : idxOrMembers{-1} {}
        Group(int idxOnlyMember) : idxOrMembers{idxOnlyMember} {}
    };

    bool processGroup(Group &group, vector<int> &res)
    {
        if (std::holds_alternative<int>(group.idxOrMembers)) {
            auto idx = std::get<int>(group.idxOrMembers);
            if (idx != -1) res.push_back(idx);
            return true;
        }

        auto &members = std::get<Group::Members>(group.idxOrMembers);
        auto countTodo = size(members);

        auto itemNonInEdges = std::stack{vector<int>{}};
        for (int i = 0; static_cast<sz>(i) < size(members); ++i) {
            if (members[i].nInEdges == 0) itemNonInEdges.push(i);
        }

        while (!itemNonInEdges.empty()) {
            auto mIdx = itemNonInEdges.top();
            itemNonInEdges.pop();
            res.push_back(members[mIdx].idx);
            --countTodo;
            for (auto idxAfter : members[mIdx].afterMemberIds) {
                if (--members[idxAfter].nInEdges == 0) itemNonInEdges.push(idxAfter);
            }
        }
        return countTodo == 0;
    }

public:
    auto sortItems(int n, int m, vector<int> &group, vector<vector<int>> &beforeItems)
            -> vector<int>
    {
        auto groups = vector<Group>(m);
        // set group[i]: bit[15:0] - groupIdx, bit[30:16] memberIdx
        for (int i = 0; i < n; ++i) {
            if (group[i] == -1) {
                group[i] = static_cast<int>(size(groups));
                groups.emplace_back(i);
            }
            else {
                auto &curGroup = groups[group[i]];
                if (std::holds_alternative<int>(curGroup.idxOrMembers)) {
                    auto &idx = std::get<int>(curGroup.idxOrMembers);
                    if (idx == -1) { idx = i; }
                    else {
                        curGroup.idxOrMembers = Group::Members{{idx}};
                    }
                }
                if (std::holds_alternative<Group::Members>(curGroup.idxOrMembers)) {
                    auto &members = std::get<Group::Members>(curGroup.idxOrMembers);
                    auto _idx = size(members);
                    members.push_back({i});
                    group[i] |= static_cast<int>(_idx) << 16;
                }
            }
        }
        m = static_cast<int>(size(groups));
        auto const getGroupIdx = [&group](int idx) { return group[idx] & ((1 << 16) - 1); };
        auto const getMemberIdx
                = [&group](int idx) { return (group[idx] >> 16) & ((1 << 15) - 1); };

        for (int i = 0; i < n; ++i) {
            auto gIdx = getGroupIdx(i);
            auto mIdx = getMemberIdx(i);
            for (int idxBefore : beforeItems[i]) {
                auto gidBefore = getGroupIdx(idxBefore);
                if (gidBefore == gIdx) {
                    auto &members = std::get<Group::Members>(groups[gIdx].idxOrMembers);
                    auto midBefore = getMemberIdx(idxBefore);
                    members[midBefore].afterMemberIds.push_back(mIdx);
                    ++members[mIdx].nInEdges;
                }
                else {
                    groups[gidBefore].afterGroupIds.push_back(gIdx);
                    ++groups[gIdx].nInEdges;
                }
            }
        }

        auto res = vector<int>{};

        auto groupsNonInEdges = std::stack{vector<int>{}};
        for (int i = 0; i < m; ++i) {
            if (groups[i].nInEdges == 0) groupsNonInEdges.push(i);
        }

        while (!groupsNonInEdges.empty()) {
            auto gIdx = groupsNonInEdges.top();
            groupsNonInEdges.pop();

            if (!processGroup(groups[gIdx], res)) break;

            for (auto idxAfter : groups[gIdx].afterGroupIds) {
                if (--groups[idxAfter].nInEdges == 0) groupsNonInEdges.push(idxAfter);
            }
        }

        if (static_cast<int>(size(res)) != n) res.clear();
        return res;
    }
};
