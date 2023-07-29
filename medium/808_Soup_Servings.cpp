using std::array;
using std::string;
using std::vector;
using sz = std::size_t;

class Solution
{
public:
    auto soupServings(int n) -> double
    {
        if (n == 0) return .5;
        if (n <= 25) return .625;
        if (n >= 4400) return 1.;

        n = (n - 1) / 25 + 1;

        //  case n = 7  (the numbers below is #round)
        //
        //  _  _  0  _  _  _  1  _
        //  _  0  _  _  _  1  _  _
        //  0  _  _  _  1  _  _  _
        //  _  _  _  1  _  _  _  2
        //  _  _  1  _  _  _  2  _
        //  _  1  _  _  _  2  _  _
        //  _  _  _  _  2  _  _  _
        //  _  _  _  _  _  _  _  X

        // dp store 2 rounds at the same time

        auto const resApB = n + n;
        auto curApB = resApB % 4;

        auto curDp = vector<double>{};
        auto prevDp = curApB == 2 ? decltype(curDp){1., (1. + .5 + .5 + .5) / 4., 0.}
                                  : decltype(curDp){.5};

        auto endPrevDp = end(prevDp);
        for (curApB += 4; curApB <= resApB; curApB += 4) {
            int a = std::max(0, curApB - n);
            int const aLast = std::min(curApB - 1,            // b >= 1
                                       (curApB / 2 + n) / 2); // 3a - b <= 3n - n

            if (sz nDp = aLast - a + 1; nDp > size(curDp)) curDp.resize(nDp);
            sz idxDp = 0u;

            auto itPrevEnd = begin(prevDp);
            auto pSum = 0.;
            if (a < 4) {
                int sumOf1 = 4 - a;
                for (int i = a; i > 0; --i) {
                    if (itPrevEnd != endPrevDp) pSum += *itPrevEnd++;
                }

                for (auto aEnd = std::min(4, aLast + 1); a < aEnd; ++a) {
                    curDp[idxDp++] = (pSum + static_cast<double>(sumOf1)) / 4.;
                    --sumOf1;
                    if (itPrevEnd != endPrevDp) pSum += *itPrevEnd++;
                }
            }
            else {
                for (int i = 0; i < 4; ++i) {
                    if (itPrevEnd == endPrevDp) break;
                    pSum += *itPrevEnd++;
                }
            }

            auto itPrevBeg = begin(prevDp);
            for (; a <= aLast; ++a) {
                curDp[idxDp++] = pSum / 4.;
                if (itPrevEnd != endPrevDp) pSum += *itPrevEnd++;
                pSum -= *itPrevBeg++;
            }

            prevDp.swap(curDp);
            endPrevDp = next(begin(prevDp), idxDp);
        }

        return prevDp.front();
    }
};
