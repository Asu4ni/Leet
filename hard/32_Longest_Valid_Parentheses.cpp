using std::array;
using std::string;
using std::vector;

class Solution
{
public:
    int longestValidParentheses(string s)
    {
        int max = 0, i = -1;
        auto stack = std::stack{vector{i}};
        ++i;

        for (char c : s) {
            if (c == '(') { stack.push(i); }
            else {
                stack.pop();
                if (stack.empty()) { stack.push(i); }
                else {
                    max = std::max(i - stack.top(), max);
                }
            }
            ++i;
        }
        return max;
    }
};

