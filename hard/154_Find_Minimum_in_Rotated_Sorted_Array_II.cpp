using std::vector;
using sz = std::size_t;

class Solution
{
public:
    int findMin(vector<int> &nums)
    {
        auto itBeg = begin(nums), itEnd = end(nums);
        while (next(itBeg) != itEnd) {
            auto itMid = next(itBeg, distance(itBeg, itEnd) / 2);
            auto itBk = prev(itEnd);

            if (itBeg == itMid) return std::min(*itBeg, *itBk);

            if (*itBeg < *itMid) {          // left- 3 > 4 | 5 | 6 > 1 > 2 -right
                if (*itMid <= *itBk) break; // left- 3 > 4 | 5 | 5   >   5 -right
                itBeg = next(itMid);
            }
            else if (*itBeg > *itMid) { // left- 6 > 1 > 2 | 3 | 4 > 5 -right
                ++itBeg;
                itEnd = next(itMid);
            }
            else {
                if (*itMid < *itBk) break; // left- 1 > 1 | 1 | 2   >   3 -right
                if (*itMid > *itBk) {      // left- 3 > 3 | 3 | 4 > 1 > 2 -right
                    itBeg = next(itMid);
                }
                else { // left-2 > (1/3) > 2 | 2 | 2 > (1/3) > 2 -right
                    ++itBeg, --itEnd;
                }
            }
        }
        return *itBeg;
    }
};
