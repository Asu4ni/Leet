using std::array;
using std::string;
using std::string_view;
using std::vector;
using sz = std::size_t;

static constexpr char chMin = 'a';
static constexpr char chMax = 'z';
static constexpr sz maxWords = 20u;
static constexpr sz maxLen = 1000u;

struct Trie
{
    void addWord(string_view strv)
    {
        auto curNodePtr = &root;
        auto itStr = begin(strv);

        // search until leaf is reached
        for (; itStr != end(strv); ++itStr) {
            auto &nxtNodePtr = curNodePtr->nxtNodePtrs[*itStr - chMin];
            if (!nxtNodePtr) break;
            curNodePtr = nxtNodePtr.get();
        }
        // add the rest of strv into Trie
        for (; itStr != end(strv); ++itStr) {
            auto &nxtNodePtr = curNodePtr->nxtNodePtrs[*itStr - chMin];
            nxtNodePtr = std::make_unique<Node>();
            curNodePtr = nxtNodePtr.get();
        }
        curNodePtr->isEndOfWord = true;
    }

    template <typename ItOutput>
    void outputPrefixEnds(string_view strv, ItOutput itOutput) const
    {
        sz pos = 0u;

        auto curNodePtr = &root;
        if (curNodePtr->isEndOfWord) *itOutput++ = pos;

        for (char ch : strv) {
            auto &nxtNodePtr = curNodePtr->nxtNodePtrs[ch - chMin];
            if (!nxtNodePtr) break;
            curNodePtr = nxtNodePtr.get();
            ++pos;
            if (curNodePtr->isEndOfWord) *itOutput++ = pos;
        }
    }

private:
    struct Node
    {
        bool isEndOfWord{false};
        array<std::unique_ptr<Node>, chMax - chMin + 1> nxtNodePtrs{};

        ~Node()
        {
            auto queue = std::queue<std::unique_ptr<Node>>{};

            auto insertChilds = [&queue](auto &node)
            {
                for (auto &ptr : node.nxtNodePtrs) {
                    if (ptr) queue.push(std::move(ptr));
                }
            };
            insertChilds(*this);
            for (; !queue.empty(); queue.pop()) { insertChilds(*queue.front()); }
        }
    } root;
};

class Solution
{
    std::bitset<maxLen> impossibleSince;

    bool composableUsing(string_view strv, sz posSince, Trie const &trie)
    {
        if (posSince == size(strv)) return true;
        if (impossibleSince.test(posSince)) return false;

        auto curSubStrv = strv.substr(posSince);
        auto prefixEnds = array<sz, maxWords>{};
        trie.outputPrefixEnds(curSubStrv, begin(prefixEnds));

        for (auto itPrefixEnd
             = std::make_reverse_iterator(std::find(begin(prefixEnds), end(prefixEnds), 0u));
             itPrefixEnd != rend(prefixEnds); ++itPrefixEnd) {

            if (composableUsing(strv, posSince + *itPrefixEnd, trie)) return true;
        }

        impossibleSince.set(posSince);
        return false;
    }

public:
    bool wordBreak(string s, vector<string> const &wordDict)
    {
        Trie trie;
        for (auto &word : wordDict) trie.addWord(word);

        impossibleSince.reset();
        return composableUsing(s, 0u, trie);
    }
};
