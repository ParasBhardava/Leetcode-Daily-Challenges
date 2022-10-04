// Problem Link : https://leetcode.com/problems/number-of-dice-rolls-with-target-sum/
/*
1155. Number of Dice Rolls With Target Sum
You have n dice and each die has k faces numbered from 1 to k.

Given three integers n, k, and target, return the number of possible ways (out of the kn total ways)
to roll the dice so the sum of the face-up numbers equals target. Since the answer may be too large,
return it modulo 109 + 7.

Input: n = 1, k = 6, target = 3
Output: 1
Explanation: You throw one die with 6 faces.
There is only one way to get a sum of 3.

Input: n = 2, k = 6, target = 7
Output: 6
Explanation: You throw two dice, each with 6 faces.
There are 6 ways to get a sum of 7: 1+6, 2+5, 3+4, 4+3, 5+2, 6+1.

Input: n = 30, k = 30, target = 500
Output: 222616187
Explanation: The answer must be returned modulo 109 + 7.

1 <= n, k <= 30
1 <= target <= 1000

*/

/*--------------------------------------------------------------------------------------------------------*/

// Brutefore recursion : GIiving TLE

class Solution {

private:
    int solve(int idx, int target, int n, int k)
    {
        if(idx == n)
        {
            if(target == 0)
                return  1;
            
            return 0;
        }
        
        int ans = 0;
        for(int i = 1; i <= k; i++)
        {
            if(i <= target)
                ans += solve(idx + 1, target - i, n, k);
        }
        
        return ans;
    }
    
public:
    int numRollsToTarget(int n, int k, int target) {
        return solve(0, target, n, k);   
        
    }
};

/*-------------------------------------------------------------------------------------------------------------------*/

// Topdown(memoization) approach :

class Solution
{
    const int MOD = 1e9 + 7;

private:
    int solve(int idx, int target, int n, int k, vector<vector<int>> &dp)
    {
        if (idx == n)
        {
            if (target == 0)
                return 1;

            return 0;
        }

        if (dp[idx][target] != -1)
            return dp[idx][target];

        int ans = 0;
        for (int i = 1; i <= k; i++)
        {
            if (i <= target)
                ans = (ans + solve(idx + 1, target - i, n, k, dp) % MOD) % MOD;
        }

        return dp[idx][target] = ans;
    }

public:
    int numRollsToTarget(int n, int k, int target)
    {

        vector<vector<int>> dp(n, vector<int>(target + 1, -1));
        return solve(0, target, n, k, dp);
    }
};

// Time : O(n * k * target)
// Space : O(n * target)
// Auxiliary recursion space

/*------------------------------------------------------------------------------------------------------------------------------*/

// Bottomup(Tabular) approach :

class Solution
{
    const int MOD = 1e9 + 7;

public:
    int numRollsToTarget(int n, int k, int target)
    {

        vector<vector<int>> dp(n + 1, vector<int>(target + 1, 0));
        dp[n][0] = 1;

        for (int idx = n - 1; idx >= 0; idx--)
        {
            for (int tar = 0; tar <= target; tar++)
            {
                int ans = 0;
                for (int i = 1; i <= k; i++)
                {
                    if (i <= tar)
                        ans = (ans + dp[idx + 1][tar - i] % MOD) % MOD;
                }

                dp[idx][tar] = ans;
            }
        }

        return dp[0][target];
    }
};

// Time : O(n * k * target)
// Space : O(n * target)
// No auxiliary recursion space is there compare to previous approach

/*-----------------------------------------------------------------------------------------------------------------------*/

// Space Optimized : Using Two 1D array of size target

class Solution
{
    const int MOD = 1e9 + 7;

public:
    int numRollsToTarget(int n, int k, int target)
    {

        vector<int> prev(target + 1, 0);
        vector<int> curr(target + 1, 0);
        prev[0] = 1;

        for (int idx = n - 1; idx >= 0; idx--)
        {
            for (int tar = 1; tar <= target; tar++)
            {
                int ans = 0;
                for (int i = 1; i <= k; i++)
                {
                    if (i <= tar)
                        ans = (ans + prev[tar - i] % MOD) % MOD;
                }

                curr[tar] = ans;
            }

            prev = curr;
        }

        return prev[target];
    }
};

// Time : O(n * k * target)
// Space : O(2 * target)

/*--------------------------------------------------------------------------------------------------------------------------*/

// SPace optimized : Using One 1D array of size target

class Solution
{
    const int MOD = 1e9 + 7;

public:
    int numRollsToTarget(int n, int k, int target)
    {

        vector<int> dp(target + 1, 0);
        dp[0] = 1;

        for (int idx = n - 1; idx >= 0; idx--)
        {
            for (int tar = target; tar >= 0; tar--)
            {
                int ans = 0;
                for (int i = 1; i <= k; i++)
                {
                    if (i <= tar)
                        ans = (ans + dp[tar - i] % MOD) % MOD;
                }

                dp[tar] = ans;
            }
        }

        return dp[target];
    }
};

// Time : O(n * k * target)
// Space : O(target)

/*-------------------------------------------------------------------------------------------------------------------*/

/*
Topic Tags : Dynemic Programming

This problem is a variation of Coin Change 2(maximum number of ways to sum coins to the amount).
Here the difference is that the total number of coins (dices) should be equal to n

*/
