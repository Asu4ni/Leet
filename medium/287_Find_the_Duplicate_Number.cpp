class Solution
{
public:
    int findDuplicate(vector<int> &nums)
    {
        int &num = nums[0];
        while (nums[num] != 0) { //
            num = std::exchange(nums[num], 0);
        }
        return num;
    }
};
