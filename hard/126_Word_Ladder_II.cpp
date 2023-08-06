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
    struct RouteRecord
    {
        Node const *nodePtr;
        sz idxRes;
        RouteRecord(Node const *nodePtr, sz idxRes) : nodePtr{nodePtr}, idxRes{idxRes} {}
    };

    sz distance(string_view a, string_view b)
    {
        return std::inner_product(begin(a), end(a), begin(b), sz{}, std::plus{},
                                  [](char a, char b) { return a == b ? sz{0u} : sz{1u}; });
    }

public:
    // find the sequence using BFS
    auto findLadders(string beginWord, string endWord, vector<string> &wordList)
            -> vector<vector<string>>
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

        if (beginNodePtr == nullptr) return res;

        for (auto it = begin(nodes), endIt = end(nodes); it != endIt; ++it) {
            for (auto itComp = next(it); itComp != endIt; ++itComp) {
                if (distance(it->word, itComp->word) == 1) {
                    it->neighbors.push_back(&*itComp);
                    itComp->neighbors.push_back(&*it);
                }
            }
        }

        { // BFS
            bool found = false;
            for (auto curNodePtrs = vector{beginNodePtr}, nxtNodePtrs = decltype(curNodePtrs){};
                 !found && !curNodePtrs.empty();
                 curNodePtrs.swap(nxtNodePtrs), nxtNodePtrs.clear()) {
                for (auto curNodePtr : curNodePtrs) curNodePtr->state = Node::State::visited;

                for (auto curNodePtr : curNodePtrs) {
                    if (curNodePtr->state == Node::State::processed) continue;

                    for (auto nxtNodePtr : curNodePtr->neighbors) {
                        if (nxtNodePtr->state != Node::State::init) continue;
                        if (nxtNodePtr == endNodePtr) found = true;
                        nxtNodePtrs.push_back(nxtNodePtr);
                        nxtNodePtr->parentPtrs.push_back(curNodePtr);
                    }

                    curNodePtr->state = Node::State::processed;
                }
            }
            if (!found) return res;
        }

        // construct result backwards
        auto routeRecs = vector<RouteRecord>{};
        auto addRecord = [&res, &routeRecs](Node const *nodePtr, sz idxRes)
        {
            res[idxRes].push_back(string{nodePtr->word});
            routeRecs.emplace_back(nodePtr, idxRes);
        };

        res.emplace_back();
        addRecord(endNodePtr, 0u);
        while (!routeRecs.empty()) {
            auto rec = routeRecs.back();
            routeRecs.pop_back();

            if (rec.nodePtr->parentPtrs.empty()) continue;

            for (auto itParPtr = next(begin(rec.nodePtr->parentPtrs)),
                      endIt = end(rec.nodePtr->parentPtrs);
                 itParPtr != endIt; ++itParPtr) {
                res.push_back(res[rec.idxRes]);
                addRecord(*itParPtr, size(res) - 1u);
            }
            addRecord(rec.nodePtr->parentPtrs.front(), rec.idxRes);
        }

        for (auto &vec : res) std::reverse(begin(vec), end(vec));
        return res;
    }
};
