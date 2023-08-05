using std::array;
using std::string;
using std::string_view;
using std::vector;
using sz = std::size_t;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
    static constexpr sz maxN = 8;

    struct Range
    {
        sz idxBeg, idxEnd;
    };

    vector<TreeNode *> nodePtrs;

    /* (0, 0)
     * (0, 1) (1, 1)
     * (0, 2) (1, 2) (2, 2)
     * ...
     */
    array<Range, (maxN + 1u) * maxN / 2u> rangesOfTreeRoots;
    auto &idxRange(sz min, sz max)
    {
        --min, --max;
        return rangesOfTreeRoots[(1u + max) * max / 2u + min];
    }

public:
    auto generateTrees(int n) -> vector<TreeNode *>
    {
        sz sizeTree = static_cast<unsigned>(n);

        // curSize = 1
        for (sz rootVal = 1u; rootVal <= sizeTree; ++rootVal) {
            auto &[idxBeg, idxEnd] = idxRange(rootVal, rootVal);
            idxBeg = size(nodePtrs);
            nodePtrs.push_back(new TreeNode{static_cast<int>(rootVal)});
            idxEnd = size(nodePtrs);
        }

        for (sz curSize = 2u; curSize <= sizeTree; ++curSize) {
            for (sz curMin = 1u, curMax = curMin + curSize - 1; curMax <= sizeTree;
                 ++curMin, ++curMax) {
                auto &[idxBeg, idxEnd] = idxRange(curMin, curMax);
                idxBeg = size(nodePtrs);

                // rootVal = curMin
                for (auto [idx, end] = idxRange(curMin + 1u, curMax); idx < end; ++idx) {
                    nodePtrs.push_back(
                            new TreeNode{static_cast<int>(curMin), nullptr, nodePtrs[idx]});
                }

                for (sz rootVal = curMin + 1; rootVal < curMax; ++rootVal) {
                    for (auto [idxL, endL] = idxRange(curMin, rootVal - 1u); idxL < endL; ++idxL) {
                        for (auto [idxR, endR] = idxRange(rootVal + 1u, curMax); idxR < endR;
                             ++idxR) {
                            nodePtrs.push_back(new TreeNode{static_cast<int>(rootVal),
                                                            nodePtrs[idxL], nodePtrs[idxR]});
                        }
                    }
                }

                // rootVal = curMax
                for (auto [idx, end] = idxRange(curMin, curMax - 1u); idx < end; ++idx) {
                    nodePtrs.push_back(
                            new TreeNode{static_cast<int>(curMax), nodePtrs[idx], nullptr});
                }
                idxEnd = size(nodePtrs);
            }
        }

        auto [idxBeg, idxEnd] = idxRange(1u, sizeTree);
        nodePtrs.erase(begin(nodePtrs), next(begin(nodePtrs), idxRange(1u, sizeTree).idxBeg));
        return nodePtrs;
    }
};
