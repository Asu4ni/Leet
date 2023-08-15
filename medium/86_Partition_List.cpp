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
    auto partition(ListNode *head, int x) -> ListNode *
    {
        if (!head) return head;

        auto nextPtrToLessEndPtr = &head;
        while (*nextPtrToLessEndPtr && (*nextPtrToLessEndPtr)->val < x) {
            nextPtrToLessEndPtr = &(*nextPtrToLessEndPtr)->next;
        }
        if (!*nextPtrToLessEndPtr) return head;

        for (auto nextPtrToCurPtr = &(*nextPtrToLessEndPtr)->next; *nextPtrToCurPtr;) {
            if ((*nextPtrToCurPtr)->val >= x) {
                nextPtrToCurPtr = &(*nextPtrToCurPtr)->next;
                continue;
            }

            auto curPtr = *nextPtrToCurPtr;
            *nextPtrToCurPtr = curPtr->next;
            curPtr->next = *nextPtrToLessEndPtr;
            *nextPtrToLessEndPtr = curPtr;

            nextPtrToLessEndPtr = &curPtr->next;
        }

        return head;
    }
};
