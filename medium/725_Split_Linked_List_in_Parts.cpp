using std::vector;
using sz = std::size_t;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

class Solution
{
    static auto size(ListNode *headPtr)
    {
        sz listSize = 0;
        for (; headPtr; headPtr = headPtr->next) ++listSize;
        return listSize;
    }

    static auto extract(ListNode *headPtr, sz n)
    {
        if (n == 0) return headPtr;
        while (--n > 0) headPtr = headPtr->next;
        return std::exchange(headPtr->next, nullptr);
    }

public:
    auto splitListToParts(ListNode *head, int k) -> vector<ListNode *>
    {
        auto const nList = size(head);
        auto const avg = nList / k;
        auto const nExtra = nList % k;

        auto res = vector<ListNode *>(k);
        sz idx = 0;
        for (; idx < nExtra; ++idx) {
            res[idx] = head;
            head = extract(head, avg + 1);
        }
        for (; idx < static_cast<sz>(k - 1); ++idx) {
            res[idx] = head;
            head = extract(head, avg);
        }
        res[idx] = head;
        return res;
    }
};
