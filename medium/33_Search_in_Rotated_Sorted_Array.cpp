using std::vector;
using sz = std::size_t;

class Solution
{
    template <typename It>
    auto biSearch(It begin, It end, int target)
    {
        if (begin == end) return end;
        auto it = std::lower_bound(begin, end, target);
        return it != end && *it == target ? it : end;
    }

    template <typename It>
    auto biSearchRotatedArr(It begin, It end, int target)
    {
        if (begin == end) return end;
        auto mid = next(begin, distance(begin, end) / 2);

        if (*mid == target) return mid;
        if (*begin == target) return begin;

        if (*begin < *mid) { // left: sorted, right: rotated
            if (*begin < target && target < *mid) {
                auto it = biSearch(begin, mid, target);
                return it == mid ? end : it;
            }

            return biSearchRotatedArr(next(mid), end, target);
        }

        if (*begin > *mid) { // left: rotated, right: sorted
            if (*mid < target && target < *begin) return biSearch(next(mid), end, target);

            auto it = biSearchRotatedArr(begin, mid, target);
            return it == mid ? end : it;
        }

        // *begin == *mid
        auto it = biSearchRotatedArr(begin, mid, target);
        if (it == mid) it = biSearchRotatedArr(next(mid), end, target);
        return it;
    }

public:
    int search(vector<int> &nums, int target)
    {
        auto it = biSearchRotatedArr(begin(nums), end(nums), target);
        return it == end(nums) ? -1 : static_cast<int>(distance(begin(nums), it));
    }
};
