using std::array;
using std::string;
using std::vector;
using sz = std::size_t;

class Solution
{
    static constexpr int maxSpeed = 10000000;

public:
    int minSpeedOnTime(vector<int> &dist, double hour)
    {
        if (hour < size(dist) - 1. + static_cast<double>(dist.back()) / maxSpeed) return -1;

        int lower = 1, upper = maxSpeed;
        while (lower < upper) {
            int speed = (lower + upper) / 2;
            auto duration = static_cast<double>(dist.back()) / speed
                            + std::accumulate(begin(dist), prev(end(dist)), 0,
                                              [speed](int sum, int dist)
                                              { return sum + (dist - 1) / speed + 1; });
            if (duration <= hour) { upper = speed; }
            else {
                lower = speed + 1;
            }
        }
        return lower;
    }
};

