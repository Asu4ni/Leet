using std::array;
using std::string;
using std::vector;

class Solution
{
public:
    int peakIndexInMountainArray(vector<int> &arr)
    {
        auto itFr = next(begin(arr)), itBk = prev(end(arr));
        while (itFr != itBk) {
            auto itMid = itFr + distance(itFr, itBk) / 2;
            if (*prev(itMid) > *itMid) { itBk = itMid; }
            else if (*next(itMid) > *itMid) {
                itFr = next(itMid);
            }
            else {
                itFr = itMid;
                break;
            }
        }
        return distance(begin(arr), itFr);
    }
};

