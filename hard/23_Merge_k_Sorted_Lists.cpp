using std::array;
using std::string;
using std::vector;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
    auto mergeKLists(vector<ListNode *> &lists) -> ListNode *
    {
        if (lists.empty()) return nullptr;
        lists.erase(remove(begin(lists), end(lists), nullptr), end(lists));

        while (size(lists) > 1) {
            for (auto itF = begin(lists), itB = prev(end(lists)); itF < itB; ++itF, --itB) {
                if ((*itF)->val > (*itB)->val) iter_swap(itF, itB);
                auto prev = *itF, pa = (*itF)->next, pb = *itB;
                while (pa && pb) {
                    auto &pLess = pa->val <= pb->val ? pa : pb;
                    prev = prev->next = pLess;
                    pLess = pLess->next;
                }
                prev->next = pa ? pa : pb;
            }
            lists.resize((size(lists) + 1) / 2);
        }
        return lists.front();
    }
};

