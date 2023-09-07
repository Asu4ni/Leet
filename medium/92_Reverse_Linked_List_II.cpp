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
    auto reverseBetween(ListNode *head, int left, int right) -> ListNode *
    {
        if (left == right) return head;

        auto ptrToNxtPtrToFront = &head;
        right -= left;
        while (--left > 0) { ptrToNxtPtrToFront = &(*ptrToNxtPtrToFront)->next; }

        auto ptrToBack = *ptrToNxtPtrToFront;

        auto prevPtr = static_cast<ListNode *>(nullptr);
        while (--right >= 0) {
            prevPtr = std::exchange(ptrToBack, std::exchange(ptrToBack->next, prevPtr));
        }

        (*ptrToNxtPtrToFront)->next = ptrToBack->next;
        *ptrToNxtPtrToFront = ptrToBack;
        ptrToBack->next = prevPtr;

        return head;
    }
};
