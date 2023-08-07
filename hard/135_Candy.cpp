using std::vector;
using sz = std::size_t;

class Solution
{
public:
    int candy(vector<int> &ratings)
    {
        int cPrev = 1;
        int sum = cPrev;

        int cPrevPeak = cPrev;
        int distToPeak = 1;
        for (auto itR = next(begin(ratings)); itR != end(ratings); ++itR) {
            int c = 1;
            if (*itR < *prev(itR)) {
                sum += distToPeak;
                if (cPrevPeak == distToPeak) {
                    ++cPrevPeak;
                    ++sum;
                }
            }
            else if (*itR > *prev(itR)) {
                c = cPrev + 1;
                sum += c;
                cPrevPeak = c;
                distToPeak = 0;
            }
            else {
                sum += c;
                cPrevPeak = c;
                distToPeak = 0;
            }

            ++distToPeak;
            cPrev = c;
        }

        return sum;
    }
};
