using std::string;
using std::string_view;
using std::vector;
using sz = std::size_t;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Codec
{
    static constexpr char separator = '/';

    string str;
    string::const_iterator it;
    void _serialize(TreeNode *rootPtr)
    {
        if (rootPtr == nullptr) return;

        str += std::to_string(rootPtr->val);
        str += separator;
        _serialize(rootPtr->left);
        str += separator;
        _serialize(rootPtr->right);
    }

    auto _deserialize() -> TreeNode *
    {
        if (*it == '/') return nullptr;

        auto &root = *new TreeNode{0};

        bool neg = false;
        if (*it == '-') {
            neg = true;
            ++it;
        }
        for (; *it != '/'; ++it) root.val = root.val * 10 + (*it - '0');
        if (neg) root.val = -root.val;

        ++it;
        root.left = _deserialize();
        ++it;
        root.right = _deserialize();
        return &root;
    }

public:
    auto serialize(TreeNode *root) -> string
    {
        str.clear();
        _serialize(root);
        return str + separator;
    }

    auto deserialize(string data) -> TreeNode *
    {
        if (data.empty()) return nullptr;
        it = begin(data);
        return _deserialize();
    }
};
