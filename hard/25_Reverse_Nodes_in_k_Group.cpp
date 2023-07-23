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
    auto reverseKGroup(ListNode *head, int k) -> ListNode *
    {
        if (k == 1) return head;

        auto prevNextRef = std::ref(head);
        auto ptrFront = head;
        while (ptrFront) {
            auto ptrBack = ptrFront;
            for (int i = 1; i < k; ++i) {
                ptrBack = ptrBack->next;
                if (!ptrBack) {
                    prevNextRef.get() = ptrFront;
                    return head;
                }
            }

            prevNextRef.get() = ptrBack;
            prevNextRef = ptrFront->next;

            auto ptrPrev = decltype(ptrFront){};
            for (auto const endPtr = ptrBack->next; ptrFront != endPtr;) {
                ptrFront = std::exchange(ptrFront->next, std::exchange(ptrPrev, ptrFront));
            }
        }
        return head;
    }
};

