using std::array;
using std::string;
using std::vector;
using sz = std::size_t;

class Solution
{
    struct Cell
    {
        int row, col;
    };
    using Option = std::bitset<9>;

    template <typename Trivial, sz maxSize>
    struct Array
    {
        array<Trivial, maxSize> arr;
        sz size = 0u;

        auto &push(Trivial val) { return arr[size++] = val; }
        auto &pop() { return arr[--size]; }

        auto begin() { return std::begin(arr); }
        auto end() { return std::next(begin(), size); }
    };
    array<array<Option, 9>, 9> options;
    Array<Cell, 9 * 9> todoHeap;

    auto delOptionsAndGetUpdatedAfterWriting(int row, int col, int num)
    {
        auto updatedOpt = std::optional{Array<Cell, (9 - 1) + (9 - 3) * 2>{}};

        auto erase = [&num, &updatedOpt, &options = options](int r, int c)
        {
            if (!options[r][c].test(num)) return true;
            if (options[r][c].count() == 1) return false;

            options[r][c].reset(num);
            updatedOpt->push({r, c});
            return true;
        };

        bool possible = true;
        for (int c = 0; c < col / 3 * 3; ++c) possible = possible && erase(row, c);
        for (int c = col / 3 * 3 + 3; c < 9; ++c) possible = possible && erase(row, c);

        for (int r = 0; r < row / 3 * 3; ++r) possible = possible && erase(r, col);
        for (int r = row / 3 * 3 + 3; r < 9; ++r) possible = possible && erase(r, col);

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                int r = i + row / 3 * 3, c = j + col / 3 * 3;
                if (r == row && c == col) continue;
                possible = possible && erase(r, c);
            }
        }

        if (!possible) {
            for (auto &[r, c] : *updatedOpt) options[r][c].set(num);
            updatedOpt.reset();
        }
        return updatedOpt;
    }

    // search the cell with the least #options
    bool search()
    {
        if (todoHeap.size == 0) return true;

        auto const comp = [&options = options](auto &cellA, auto &cellB)
        { return options[cellA.row][cellA.col].count() > options[cellB.row][cellB.col].count(); };

        using std::begin, std::end;
        std::make_heap(begin(todoHeap), end(todoHeap), comp);
        std::pop_heap(begin(todoHeap), end(todoHeap), comp);
        auto [row, col] = todoHeap.pop();

        if (options[row][col].none()) return false;

        auto origOptions = options[row][col];
        for (int i = 0; i < 9; ++i) {
            if (!origOptions.test(i)) continue;

            auto updatedOpt = delOptionsAndGetUpdatedAfterWriting(row, col, i);
            if (!updatedOpt) continue;

            if (search()) {
                options[row][col].reset();
                options[row][col].set(i);
                return true;
            }
            for (auto &[r, c] : *updatedOpt) options[r][c].set(i);
        }
        options[row][col] = origOptions;
        todoHeap.push({row, col});

        return false;
    }

public:
    void solveSudoku(vector<vector<char>> &board);
};


void Solution::solveSudoku(vector<vector<char>> &board)
{
    // setup options:
    //  '.': all 9 numbers
    //  0-9: only such number
    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            if (board[r][c] == '.') { options[r][c].set(); }
            else {
                options[r][c].set(board[r][c] - '1');
            }
        }
    }

    // remove impossible options
    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            if (board[r][c] == '.') continue;
            delOptionsAndGetUpdatedAfterWriting(r, c, board[r][c] - '1');
        }
    }

    // construct todos if #option > 1
    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            if (options[r][c].count() > 1) todoHeap.push({r, c});
        }
    }

    if (!search()) return;

    auto const getOption = [](Option opt)
    {
        for (int i = 0; i < 9; ++i) {
            if (opt.test(i)) return i;
        }
        return -1;
    };

    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            if (board[r][c] != '.') continue;
            board[r][c] = getOption(options[r][c]) + '1';
        }
    }
}

