using std::vector;
using sz = std::size_t;

class Solution
{
public:
    auto maxSlidingWindow(vector<int> &nums, int k) -> vector<int>
    {
        auto res = vector<int>{};
        if (k == 1) {
            res.swap(nums);
            return res;
        }
        res.resize(size(nums) - static_cast<sz>(k - 1));

        // queue operation to store non-increasing sequence in the window
        auto itQBeg = begin(nums), itQEnd = itQBeg;
        auto const push = [&itQBeg, &itQEnd](int num)
        {
            while (itQBeg != itQEnd && num > *prev(itQEnd)) --itQEnd;
            *itQEnd = num;
            ++itQEnd;
        };
        auto const pop = [&itQBeg, &itQEnd](int num)
        {
            // assert(itQBeg != itQEnd && num <= *itQBeg);
            if (num == *itQBeg) ++itQBeg;
        };

        // store nums in the window
        auto numsWindow = vector(begin(nums), next(begin(nums), k - 1));
        auto itWFront = begin(numsWindow);

        auto itNum = begin(nums);
        for (; k > 1; --k, ++itNum) push(*itNum);

        for (auto itRes = begin(res); itNum != end(nums); ++itNum, ++itRes) {
            push(*itNum);
            *itRes = *itQBeg;
            pop(*itWFront);

            *itWFront = *itNum;
            ++itWFront;
            if (itWFront == end(numsWindow)) itWFront = begin(numsWindow);
        }

        return res;
    }
};
