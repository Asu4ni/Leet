using std::vector;
using sz = std::size_t;

class Solution
{
    struct Rec
    {
        int height;
        int right;

        Rec(int height, int right) : height(height), right(right) {}
        friend bool operator<(Rec const &a, Rec const &b)
        {
            return a.height < b.height || (a.height == b.height && a.right < b.right);
        }
    };

public:
    auto getSkyline(vector<vector<int>> &buildings) -> vector<vector<int>>
    {
        auto res = vector<vector<int>>{{buildings[0][0], buildings[0][2]}};

        auto pq = std::priority_queue<Rec>{};
        auto const prevH = [&res]() -> int & { return res.back()[1]; };
        auto const prevX = [&res]() -> int & { return res.back()[0]; };

        auto processUntil = [&pq, &prevH, &prevX, &res](unsigned x)
        {
            while (!pq.empty()) {
                auto curR = pq.top().right;
                if (static_cast<unsigned>(curR) >= x) break;
                pq.pop();
                if (curR <= prevX()) continue;

                while (!pq.empty() && pq.top().right <= curR) pq.pop();
                auto curH = pq.empty() ? 0 : pq.top().height;
                if (curH != prevH()) res.push_back(vector{curR, curH});
            }
        };

        // presumption: buildings is sorted by left in non-decreasing order
        for (auto &v : buildings) {
            auto [left, right, height] = std::tie(v[0], v[1], v[2]);

            processUntil(left);
            // process left
            if (pq.empty() || height > pq.top().height) {
                if (prevX() == left) { prevH() = height; }
                else if (height != prevH()) {
                    res.push_back(vector{left, height});
                }
            }
            // process right later
            pq.emplace(height, right);
        }

        processUntil(std::numeric_limits<unsigned>::max());
        return res;
    }
};
