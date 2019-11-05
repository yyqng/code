#include<stdlib.h>
#include<iostream>
#include<vector>
#include <stack>
using namespace std;
class Solution {
public:
    int maxSubArray(vector<int>& nums);
    int maxSubArrayTest();
    bool searchMatrix(vector<vector<int>>& matrix, int target);
    bool searchMatrixTest();
    int minCostClimbingStairs(vector<int>& cost);
    void minCostClimbingStairsTest();
    int lengthOfLIS(vector<int>& nums);
    int lengthOfLIS_better(vector<int>& nums);
    void lengthOfLISTest();
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites);
    void findOrderTest();

};
