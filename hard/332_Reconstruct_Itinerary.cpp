using std::array, std::vector;
using std::begin, std::end, std::next, std::size;
using std::string, std::string_view;
using sz = std::size_t;

class Solution
{
    using IdxAirport = std::uint16_t;
    struct Airport
    {
        string name;
        vector<IdxAirport> nextAirportIds;
        sz idxNext = 0;
    };

public:
    auto findItinerary(vector<vector<string>> &tickets) -> vector<string>
    {
        auto airportIds = std::map<string, IdxAirport>{};
        for (auto const &ticket : tickets) {
            airportIds.try_emplace(ticket[0]);
            airportIds.try_emplace(ticket[1]);
        }

        auto airports = vector<Airport>(size(airportIds));
        {
            auto curId = IdxAirport{0};
            for (auto &[name, id] : airportIds) {
                id = curId;
                airports[id].name = name;
                ++curId;
            }
        }

        for (auto const &ticket : tickets) {
            airports[airportIds[ticket[0]]].nextAirportIds.push_back(airportIds[ticket[1]]);
        }
        for (auto &airport : airports) {
            std::sort(begin(airport.nextAirportIds), end(airport.nextAirportIds));
        }

        auto res = vector<string>(size(tickets) + 1);
        sz idxRes = size(res) - 1;
        for (auto dfsStack = std::stack{vector<IdxAirport>{airportIds["JFK"]}};
             !dfsStack.empty();) {
            auto &airport = airports[dfsStack.top()];

            if (airport.idxNext == size(airport.nextAirportIds)) {
                res[idxRes] = airport.name;
                --idxRes;
                dfsStack.pop();
                continue;
            }

            dfsStack.push(airport.nextAirportIds[airport.idxNext]);
            ++airport.idxNext;
        }

        return res;
    }
};
