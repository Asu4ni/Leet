using std::array;
using std::string;
using std::string_view;
using std::vector;
using sz = std::size_t;

class Solution
{
    struct Node
    {
        enum class State
        {
            init,
            visited,
            processed
        };

        State state = State::init;
        string_view word;
        vector<Node *> neighbors;
        vector<Node *> parentPtrs;
        Node(string_view word) : word{word} {}
    };

    sz distance(string_view a, string_view b)
    {
        return std::inner_product(begin(a), end(a), begin(b), sz{}, std::plus{},
                                  [](char a, char b) { return a == b ? sz{0u} : sz{1u}; });
    }

public:
    // find the sequence using BFS
    int ladderLength(string beginWord, string endWord, vector<string> &wordList)
    {
        auto res = vector<vector<string>>{};

        // prepare graph for BFS
        auto nodes = vector<Node>{};
        auto [beginNodePtr, endNodePtr] = [&beginWord, &endWord, &wordList, &nodes]()
        {
            auto idxBegOpt = std::optional<sz>{};
            auto idxEndOpt = std::optional<sz>{};
            for (auto const &word : wordList) {
                if (!idxEndOpt && word == endWord) { idxEndOpt.emplace(nodes.size()); }
                else if (!idxBegOpt && word == beginWord) {
                    idxBegOpt.emplace(nodes.size());
                }
                nodes.emplace_back(word);
            }

            if (!idxEndOpt) return std::tuple<Node *, Node *>{};
            if (!idxBegOpt) {
                idxBegOpt.emplace(nodes.size());
                nodes.emplace_back(beginWord);
            }
            return std::tuple{&nodes[*idxBegOpt], &nodes[*idxEndOpt]};
        }();

        if (beginNodePtr == nullptr) return 0;

        for (auto it = begin(nodes), endIt = end(nodes); it != endIt; ++it) {
            for (auto itComp = next(it); itComp != endIt; ++itComp) {
                if (distance(it->word, itComp->word) == 1) {
                    it->neighbors.push_back(&*itComp);
                    itComp->neighbors.push_back(&*it);
                }
            }
        }

        // BFS
        int round = 1;
        for (auto curNodePtrs = vector{beginNodePtr}, nxtNodePtrs = decltype(curNodePtrs){};
             !curNodePtrs.empty(); curNodePtrs.swap(nxtNodePtrs), nxtNodePtrs.clear()) {
            ++round;
            for (auto curNodePtr : curNodePtrs) curNodePtr->state = Node::State::visited;

            for (auto curNodePtr : curNodePtrs) {
                if (curNodePtr->state == Node::State::processed) continue;

                for (auto nxtNodePtr : curNodePtr->neighbors) {
                    if (nxtNodePtr->state != Node::State::init) continue;
                    if (nxtNodePtr == endNodePtr) return round;
                    nxtNodePtrs.push_back(nxtNodePtr);
                    nxtNodePtr->parentPtrs.push_back(curNodePtr);
                }

                curNodePtr->state = Node::State::processed;
            }
        }

        return 0;
    }
};
