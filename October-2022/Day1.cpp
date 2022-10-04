/*

91. Decode Ways
Problem Link : https://leetcode.com/problems/decode-ways/

A message containing letters from A-Z can be encoded into numbers using the following mapping :

'A' -> "1"
'B' -> "2"
...
'Z' -> "26"

To decode an encoded message, all the digits must be grouped then mapped back into letters using the reverse of the mapping above (there may be multiple ways). For example, "11106" can be mapped into:
"AAJF" with the grouping (1 1 10 6)
"KJF" with the grouping (11 10 6)
Note that the grouping (1 11 06) is invalid because "06" cannot be mapped into 'F' since "6" is different from "06".
Given a string s containing only digits, return the number of ways to decode it.
The test cases are generated so that the answer fits in a 32-bit integer

Input: s = "12"
Output: 2
Explanation: "12" could be decoded as "AB" (1 2) or "L" (12).

Input: s = "226"
Output: 3
Explanation: "226" could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).

Input: s = "06"
Output: 0
Explanation: "06" cannot be mapped to "F" because of the leading zero ("6" is different from "06").

*/

/*----------------------------------------------------------------------------------------------------------------------------*/

// Using Bruteforce Recursion
// Giving TLE in case like this : "111111111111111111111111111111111111111111111"

class Solution
{

private:
    int solve(int idx, int n, string &s)
    {
        if (idx == n)
            return 1;

        if (s[idx] == '0')
            return 0;

        int pickSingle = solve(idx + 1, n, s);
        int pickDouble = 0;
        if (idx + 1 < n && (s[idx] == '1' || s[idx] == '2' && s[idx + 1] < '7'))
            pickDouble = solve(idx + 2, n, s);

        return pickSingle + pickDouble;
    }

public:
    int numDecodings(string s)
    {

        int n = s.size();
        return solve(0, n, s);
    }
};

/*-------------------------------------------------------------------------------------------------------------------------*/

// Using Memoization(Topdown approach)
// Lets add dp array to the solution to store already calculated subproblems answer.

class Solution
{

private:
    int solve(int idx, int n, string &s, vector<int> &dp)
    {
        if (idx == n)
            return 1;

        if (s[idx] == '0')
            return 0;

        if (dp[idx] != -1)
            return dp[idx];

        int pickSingle = solve(idx + 1, n, s, dp);

        int pickDouble = 0;
        if (idx + 1 < n && (s[idx] == '1' || s[idx] == '2' && s[idx + 1] < '7'))
            pickDouble = solve(idx + 2, n, s, dp);

        return dp[idx] = pickSingle + pickDouble;
    }

public:
    int numDecodings(string s)
    {

        int n = s.size();
        vector<int> dp(n, -1);
        return solve(0, n, s, dp);
    }
};

// Time : O(N)
// Space : O(N)

/*------------------------------------------------------------------------------------------------------------------------*/

// Uisng Tabular(Bottomup) approach
// Lets's remove the extra auxiliary recurtion stack space that is used in previous approach
// Now it is easy to comeup with bottomup approach from topdown approach.

class Solution
{
public:
    int numDecodings(string s)
    {

        int n = s.size();

        vector<int> dp(n + 1);
        dp[n] = 1;

        for (int i = n - 1; i >= 0; i--)
        {
            if (s[i] == '0')
                dp[i] = 0;

            else
            {
                dp[i] = dp[i + 1];
                if (i < n - 1 && (s[i] == '1' || s[i] == '2' && s[i + 1] < '7'))
                    dp[i] += dp[i + 2];
            }
        }

        return s.empty() ? 0 : dp[0];
    }
};

// Time : O(N)
// Space : O(N)

/*-----------------------------------------------------------------------------------------------------------------------*/

// Optimal solution
// Look at the previous solution our current state answer is based on previously computed two state's  answer.
// So for calculating current answer we require only previously computed two state's answer,
// so instead of using whole n size dp array let's take two variable
// which store the previously computed answer based on that we are computing current answer.

class Solution
{
public:
    int numDecodings(string s)
    {

        int n = s.size();
        if (n == 0)
            return 0;

        int prevToPrev = 1, prev = 1, curr;

        for (int i = n - 1; i >= 0; i--)
        {
            if (s[i] == '0')
                curr = 0;

            else
            {
                curr = prev;
                if (i < n - 1 && (s[i] == '1' || s[i] == '2' && s[i + 1] < '7'))
                    curr += prevToPrev;
            }

            prevToPrev = prev;
            prev = curr;
        }

        return curr;
    }
};

// Time : O(N)
// Space : O(1)

/*----------------------------------------------------------------------------------------------------------------------*/

/*
Topic Tags : Dynemic Programming, String


This is one the most classic and standard DP problem on String.
Idea is really simple,
We at every index in the string we have got 2 choices :

Pick only current element as a single value between[1 - 9]
In case of single pick, element should not be '0' as it is invalid. So if current element is '0 then we will return 0;

Pick 2 elements i.e current as well as next element to make a couple. This value will be [10, 26].
Thus we solve the problem recursively with the above 2 choices and whenever we reach the end i.e index == n simply return 1.
Which means that we have got one way to decode the string.

Here, I write recursive solution that gives TLE, then I converted into memoization and tabular approach and then space optimized solution using above intuition.
*/
