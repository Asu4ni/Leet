using std::vector;
using sz = std::size_t;

class Solution
{
    template <typename It>
    bool biSearchRotatedArr(It begin, It end, int target)
    {
        if (begin == end) return false;
        auto mid = next(begin, distance(begin, end) / 2);

        if (*begin == target || *mid == target) return true;

        if (*begin < *mid) { // left: sorted, right: rotated
            if (*begin < target && target < *mid) return std::binary_search(begin, mid, target);

            return biSearchRotatedArr(next(mid), end, target);
        }

        if (*begin > *mid) { // left: rotated, right: sorted
            if (*mid < target && target < *begin) return std::binary_search(next(mid), end, target);

            return biSearchRotatedArr(begin, mid, target);
        }

        // *begin == *mid
        if( biSearchRotatedArr(begin, mid, target)) return true;
        return biSearchRotatedArr(next(mid), end, target);
    }

public:
    int search(vector<int> &nums, int target)
    {
        return biSearchRotatedArr(begin(nums), end(nums), target);
    }
};
