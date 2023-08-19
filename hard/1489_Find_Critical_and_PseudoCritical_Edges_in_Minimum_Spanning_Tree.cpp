using std::array;
using std::string;
using std::string_view;
using std::vector;
using sz = std::size_t;

template <auto maxNodes>
struct DisjointSet
{
    using Idx = std::uint8_t;

    void initSet(Idx nOfNodes)
    {
        std::iota(std::begin(setIds), std::next(begin(setIds), nOfNodes), Idx{});
        setCount = nOfNodes;
    }
    void unite(Idx idxNode0, Idx idxNode1)
    {
        // assert(!inSameSet(idxNode0, idxNode1));
        setIds[getSetIdx(idxNode0)] = getSetIdx(idxNode1);
        --setCount;
    }
    bool inSameSet(Idx idxNode0, Idx idxNode1)
    {
        return getSetIdx(idxNode0) == getSetIdx(idxNode1);
    }
    auto getNofSets() const { return setCount; }

private:
    Idx getSetIdx(Idx idxNode)
    {
        auto setIdx = idxNode;
        while (setIdx != setIds[setIdx]) setIdx = setIds[setIdx];
        setIds[idxNode] = setIdx;
        return setIdx;
    }

    array<Idx, maxNodes> setIds;
    Idx setCount;
};

class Solution
{
    static constexpr sz maxV = 100;

public:
    auto findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>> &edges)
            -> vector<vector<int>>
    {
        auto res = vector{vector<int>{}, vector<int>{}};
        auto &edgesCrit = res[0];
        auto &edgesPsCrit = res[1];

        // each edge[2]: bit[15:0] - weight, bit[30:16] - idx
        for (sz i = 0; i < size(edges); ++i) edges[i][2] |= static_cast<int>(i << 16);
        auto const getIdx = [](auto const &edge)
        {
            static constexpr int mask = ((1 << 15) - 1) << 16;
            return (edge[2] & mask) >> 16;
        };
        auto const getWeight = [](auto const &edge)
        {
            static constexpr int mask = (1 << 15) - 1;
            return edge[2] & mask;
        };
        std::sort(begin(edges), end(edges),
                  [&getWeight](auto const &e1, auto const &e2)
                  {
                      static constexpr int mask = (1 << 16) - 1;
                      return getWeight(e1) < getWeight(e2);
                  });

        auto set = DisjointSet<maxV>{};
        auto const mstWeight = [&n, &edges, &set, &getWeight](auto itEdgeExcluded)
        {
            int weight = 0;
            auto const exec = [&set, &weight, &getWeight](auto const &edge)
            {
                if (set.inSameSet(edge[0], edge[1])) return;
                set.unite(edge[0], edge[1]);
                weight += getWeight(edge);
            };
            auto itEdge = begin(edges);
            for (; set.getNofSets() > 1 && itEdge != itEdgeExcluded; ++itEdge) exec(*itEdge);
            if (itEdge != end(edges)) {
                ++itEdge;
                for (; set.getNofSets() > 1 && itEdge != end(edges); ++itEdge) exec(*itEdge);
            }
            return set.getNofSets() > 1 ? std::numeric_limits<int>::max() : weight;
        };

        set.initSet(n);
        auto minWeight = mstWeight(end(edges));

        for (auto itEdge = begin(edges); itEdge != end(edges); ++itEdge) {
            set.initSet(n);
            if (mstWeight(itEdge) > minWeight) { edgesCrit.push_back(getIdx(*itEdge)); }
            else {
                set.initSet(n);
                set.unite((*itEdge)[0], (*itEdge)[1]);
                if (mstWeight(itEdge) + getWeight(*itEdge) == minWeight) {
                    edgesPsCrit.push_back(getIdx(*itEdge));
                }
            }
        }
        return res;
    }
};
