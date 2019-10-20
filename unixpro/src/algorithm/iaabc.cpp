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
