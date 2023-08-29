using std::string;
using std::string_view;
using std::vector;
using sz = std::size_t;

class Solution
{
public:
    int bestClosingTime(string customers)
    {
        int relativePenalty = 0;
        int minRP = 0;
        int posMinRP = 0;

        for (int i = 0; i < static_cast<int>(size(customers)); ++i) {
            if (customers[i] == 'Y') { --relativePenalty; }
            else {
                ++relativePenalty;
            }

            if (relativePenalty < minRP) {
                minRP = relativePenalty;
                posMinRP = i + 1;
            }
        }

        return posMinRP;
    }
};
