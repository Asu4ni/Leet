using std::array;
using std::string;
using std::vector;

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
    static constexpr int nMax = 20;

public:
    auto allPossibleFBT(int n) -> vector<TreeNode *>
    {
        auto res = vector<TreeNode *>{};
        if (n % 2 == 0) return res;
        if (n == 1) {
            res.push_back(new TreeNode{0});
            return res;
        }

        // trees of 1 node, 3 nodes, ...
        // init with the 1-node tree
        auto treesOfKNodes = vector{new TreeNode{0}};
        auto begIdsOfKNodesTree = array<decltype(treesOfKNodes)::size_type, (nMax + 1) / 2>{
                0u, size(treesOfKNodes)};

        auto insertTrees
                = [&treesOfKNodes, &begIdsOfKNodesTree](auto &vec, int nOfLeft, int nOfRight)
        {
            for (auto idxLeft = begIdsOfKNodesTree[nOfLeft / 2],
                      endLeft = begIdsOfKNodesTree[nOfLeft / 2 + 1];
                 idxLeft < endLeft; ++idxLeft) {
                for (auto idxRight = begIdsOfKNodesTree[nOfRight / 2],
                          endRight = begIdsOfKNodesTree[nOfRight / 2 + 1];
                     idxRight < endRight; ++idxRight) {
                    vec.push_back(new TreeNode{0, treesOfKNodes[idxLeft], treesOfKNodes[idxRight]});
                }
            }
        };

        for (int k = 3; k <= n; k += 2) {
            auto &vecToInsert = k == n ? res : treesOfKNodes;

            for (int nOfLeft = 1; nOfLeft < k; nOfLeft += 2) {
                insertTrees(vecToInsert, nOfLeft, k - nOfLeft - 1);
            }

            if (k < n) begIdsOfKNodesTree[k / 2 + 1] = size(treesOfKNodes);
        }

        return res;
    }
};

