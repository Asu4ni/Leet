using std::vector;
using sz = std::size_t;

class Solution
{
    struct Line
    {
        int nx, ny, d2;
        Line(int x1, int y1, int x2, int y2) : nx{y1 - y2}, ny{x2 - x1}
        {
            if (nx < 0) { nx = -nx, ny = -ny; }
            else if (nx == 0 && ny < 0) {
                ny = -ny;
            }
            int div = std::gcd(nx, ny);
            nx /= div, ny /= div;

            d2 = nx * x1 + ny * y1;
        }
        friend bool operator==(Line const &a, Line const &b)
        {
            return a.nx == b.nx && a.ny == b.ny && a.d2 == b.d2;
        }
    };

public:
    int maxPoints(vector<vector<int>> &points)
    {
        if (size(points) == 1) return 1;

        auto lineHash = [](Line const &l)
        {
            static constexpr auto h = std::hash<int>{};
            return h(l.nx) ^ h(l.ny) ^ h(l.d2);
        };
        auto counts = std::unordered_map<Line, sz, decltype(lineHash)>{
                points.size() * points.size(), lineHash};

        for (auto it1 = begin(points); it1 != end(points); ++it1) {
            for (auto it2 = next(it1); it2 != end(points); ++it2) {
                ++counts[Line{(*it1)[0], (*it1)[1], (*it2)[0], (*it2)[1]}];
            }
        }

        auto maxNofSameLine = max_element(counts.begin(), counts.end(),
                                          [](auto &a, auto &b) { return a.second < b.second; })
                                      ->second;
        // ans * (ans - 1) / 2 = max
        return 1 + static_cast<int>(std::sqrt(2. * maxNofSameLine));
    }
};
