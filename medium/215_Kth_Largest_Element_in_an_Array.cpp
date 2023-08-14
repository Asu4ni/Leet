using std::vector;
using sz = std::size_t;

class Solution
{
    int median3(int n1, int n2, int n3)
    {
        if (n1 < n2) {
            if (n2 < n3) return n2;
            return n1 < n3 ? n3 : n1;
        }
        // n2 <= n1
        if (n1 < n3) return n1;
        return n2 < n3 ? n3 : n2;
    }

    template <typename It>
    void nth_element(It itBegin, It itTarget, It itEnd)
    {
        while (distance(itBegin, itEnd) > 3) {
            auto itMid = next(itBegin, distance(itBegin, itEnd) / 2);
            int pivot = median3(*itMid, *prev(itMid), *next(itMid));

            auto itCut = itBegin, itBk = itEnd;
            while (true) {
                while (*--itBk > pivot)
                    ;
                while (*itCut < pivot) ++itCut;
                if (itCut >= itBk) break;
                iter_swap(itCut, itBk);
                ++itCut;
            }

            if (itCut <= itTarget) itBegin = itCut;
            else
                itEnd = itCut;
        }

        if (distance(itBegin, itEnd) < 2) return;

        if (itBegin[1] < itBegin[0]) std::swap(itBegin[0], itBegin[1]);
        if (distance(itBegin, itEnd) == 3) {
            if (itBegin[2] < itBegin[1]) std::swap(itBegin[1], itBegin[2]);
            if (itBegin[1] < itBegin[0]) std::swap(itBegin[0], itBegin[1]);
        }
    }

public:
    int findKthLargest(vector<int> &nums, int k)
    {
        auto itTarget = next(begin(nums), size(nums) - k);
        // std::nth_element(begin(nums), itTarget, end(nums));
        nth_element(begin(nums), itTarget, end(nums));
        return *itTarget;
    }
};
