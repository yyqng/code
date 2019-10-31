#include "iaabc.h"

int Solution::maxSubArray(vector<int>& nums)
{
    if (nums.size() == 0) {
        return 0;
    }
    int max  = nums[0];
    int tmpSum = nums[0];
    for(int i = 1; i < nums.size(); ++i) {
        if( tmpSum < 0) {
            tmpSum = nums[i];
        } else {
            tmpSum += nums[i];
        }
        if( max  < tmpSum) {
            max  = tmpSum;
        }
    }
    return max;
}

int Solution::maxSubArrayTest()
{
    vector<int> nums = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
    printf("Result of maxSubArray(nums) is %d\n", maxSubArray(nums));
    return 0;
}

bool bruceSearch(vector<vector<int>>& a, int target)
{
    for(int i = 0; i < a.size(); ++i) {
        for(int j = 0; j < a[i].size(); ++j) {
            if(a[i][j] == target) {
                return true;
            }
        }
    }
    return false;
}

bool binarySearch(vector<int>& a, int start, int end, int target)
{
    while(start <= end) {
        if(start == end) {
            if(a[start] == target) {
                return true;
            } else {
                return false;
            }
        }
        int middle = (start + end) / 2;
        if(a[middle] < target) {
            start = middle + 1;
        } else if(a[middle] > target) {
            end = middle - 1;
        } else {
            return true;
        }
    }
    return false;
}

bool binarySearchColunm(vector<vector<int>>& a, int colunm, int start, int end, int target)
{
    while(start <= end) {
        if(start == end) {
            if(a[start][colunm] == target) {
                return true;
            } else {
                return false;
            }
        }
        int middle = (start + end) / 2;
        if(a[middle][colunm] < target) {
            start = middle + 1;
        } else if(a[middle][colunm] > target) {
            end = middle - 1;
        } else {
            return true;
        }
    }
    return false;
}

bool searchMatrix2(vector<vector<int>>& matrix, int i, int j, int m, int n, int target)
{
    if(i == m) {
        if(binarySearch(matrix[i], j, n, target)) {
            return true;
        } else {
            return false;
        }
    }
    if(i + 1 == m) {
        if(binarySearch(matrix[i], j, n, target)||
           binarySearch(matrix[m], j, n, target)) {
            return true;
        } else {
            return false;
        }
    }
    if(j == n) {
        if(binarySearchColunm(matrix, j, i, m, target)) {
            return true;
        } else {
            return false;
        }
    }
    if(j + 1 == n) {
        if(binarySearchColunm(matrix, j, i, m, target) ||
           binarySearchColunm(matrix, n, i, m, target)) {
            return true;
        } else {
            return false;
        }
    }
    int p = (i + m) / 2;
    int q = (j + n) / 2;
    if( matrix[p][q] == target) {
        return true;
    } else if( matrix[p][q] > target && searchMatrix2(matrix, i, j, p, q, target)) {
        return true;
    } else if(searchMatrix2(matrix, p, q, m, n, target)) {
        return true;
    }
    if (p + 1 <= m && j <= q - 1 && searchMatrix2(matrix, p + 1, j, m, q - 1, target)) {
        return true;
    }
    if (i <= p - 1 && q + 1 <= n && searchMatrix2(matrix, i, q + 1, p - 1, n, target)) {
        return true;
    }
    return false;
}

bool Solution::searchMatrix(vector<vector<int>>& matrix, int target)
{
    if(matrix.size() == 0 || matrix[0].size()== 0) {
        return false;
    }
    //132ms
    for(int i = 0; i < matrix.size(); ++i) {
        int start = 0;
        int end = matrix[i].size() - 1;
        if(binarySearch(matrix[i], start, end, target)) {
            return true;
        }
    }
    return false;

    //1080ms
    //return bruceSearch(matrix, target);

    //998ms
    //return searchMatrix2(matrix, 0, 0, matrix.size() - 1, matrix[0].size() - 1, target);
}

bool Solution::searchMatrixTest()
{
    //vector<vector<int>> matrix = {{1,   4,  7, 11, 15},
    //                              {2,   5,  8, 12, 19},
    //                              {3,   6,  9, 16, 22},
    //                              {10, 13, 14, 17, 24},
    //                              {18, 21, 23, 26, 30}};
    //printf("searchMatrix(matrix, 5)  = %d\n", searchMatrix(matrix, 5));
    //printf("searchMatrix(matrix, 20) = %d\n", searchMatrix(matrix, 20));

    //vector<vector<int>> matrix = {{1,2,3,4,5},
    //                              {6,7,8,9,10},
    //                              {11,12,13,14,15},
    //                              {16,17,18,19,20},
    //                              {21,22,23,24,25}};
    //printf("searchMatrix(matrix, 15)  = %d\n", searchMatrix(matrix, 15));

    vector<vector<int>> matrix = {{1}, {3}, {5}};
    //vector<int> tmpV = {-1, 3};
    //matrix.push_back(tmpV);
    printf("searchMatrix(matrix, 0)  = %d\n", searchMatrix(matrix, 0));
    return true;
}

int Solution::minCostClimbingStairs(vector<int>& cost)
{
    int sum[3] = {cost[0], cost[1], 0};
    for(int i = 2; i < cost.size(); ++i)
    {
        if(sum[1] < sum[0])
            sum[2] = sum[1] + cost[i];
        else
            sum[2] = sum[0] + cost[i];
        sum[0] = sum[1];
        sum[1] = sum[2];
    }
    if(sum[0] < sum[1])
        return sum[0];
    else
        return sum[1];
}

void Solution::minCostClimbingStairsTest()
{
    vector<int> cost = {0, 0, 0, 1};
    //vector<int> cost = {0, 0, 0, 0};
    //vector<int> cost = {10, 15, 20};
    //vector<int> cost = {1, 100, 1, 1, 1, 100, 1, 1, 100, 1};
    int ret = minCostClimbingStairs(cost);
    printf("min cost is %d\n", ret);
}

int Solution::lengthOfLIS_better(vector<int>& nums)
{
    if(nums.size() == 0)
        return 0;
    vector<int> results;
    for(int i = 0; i < nums.size(); ++i)
    {
        vector<int>::iterator it = lower_bound(results.begin(), results.end(), nums[i]);
        if(it == results.end())
            results.push_back(nums[i]);
        else
            *it = nums[i];
    }
    return results.size();
}

int Solution::lengthOfLIS(vector<int>& nums)
{
    if(nums.size() == 0)
        return 0;
    vector<int> dp(nums.size(), 1);
    int ret = dp[0];
    for(int i = 1; i < nums.size(); ++i)
    {
        int j = i - 1;
        for(; j >= 0; --j)
        {
            if(nums[j] < nums[i] && dp[i] < dp[j] + 1)
                dp[i] = dp[j] + 1;
        }
        if(ret < dp[i])
            ret = dp[i];
    }
    return ret;
}

void Solution::lengthOfLISTest()
{
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    //vector<int> nums = {1, 3, 6, 7, 9, 4, 10, 5, 6};
    //vector<int> nums = {2, 2};
    int ret = lengthOfLIS(nums);
    ret = lengthOfLIS_better(nums);
    printf("lengthOfLIS is %d\n", ret);
}
