using std::array;
using std::string;
using std::vector;
using sz = std::size_t;

class Solution
{
public:
    int trap(vector<int> &height)
    {
        auto prefixMaxes = vector<int>{};
        std::partial_sum(begin(height), end(height), std::back_inserter(prefixMaxes),
                         [](int a, int b) { return std::max(a, b); });

        int sum = 0;

        int postfixMax = 0;
        for (auto itPreMax = rbegin(prefixMaxes), itH = rbegin(height); itH < rend(height);
             ++itPreMax, ++itH) {
            if (*itH > postfixMax) postfixMax = *itH;

            sum += std::min(postfixMax, *itPreMax) - *itH;
        }
        return sum;
    }
};
