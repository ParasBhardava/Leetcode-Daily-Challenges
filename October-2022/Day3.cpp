// https://leetcode.com/problems/minimum-time-to-make-rope-colorful/
/*

1578. Minimum Time to Make Rope Colorful

Alice has n balloons arranged on a rope. You are given a 0-indexed string colors where colors[i]
is the color of the ith balloon.

Alice wants the rope to be colorful. She does not want two consecutive balloons to be of the same color,
so she asks Bob for help. Bob can remove some balloons from the rope to make it colorful.
You are given a 0-indexed integer array neededTime where neededTime[i] is the time (in seconds)
that Bob needs to remove the ith balloon from the rope.

Return the minimum time Bob needs to make the rope colorful.

Input: colors = "abaac", neededTime = [1,2,3,4,5]
Output: 3
Explanation: In the above image, 'a' is blue, 'b' is red, and 'c' is green.
Bob can remove the blue balloon at index 2. This takes 3 seconds.
There are no longer two consecutive balloons of the same color. Total time = 3.

Input: colors = "abc", neededTime = [1,2,3]
Output: 0
Explanation: The rope is already colorful. Bob does not need to remove any balloons from the rope.

Input: colors = "aabaa", neededTime = [1,2,3,4,1]
Output: 2
Explanation: Bob will remove the ballons at indices 0 and 4. Each ballon takes 1 second to remove.
There are no longer two consecutive balloons of the same color. Total time = 1 + 1 = 2.

n == colors.length == neededTime.length
1 <= n <= 10^5
1 <= neededTime[i] <= 10^4
colors contains only lowercase English letters.

*/

/*----------------------------------------------------------------------------------------------------------------*/

// Using Greedy approach

class Solution
{
public:
    int minCost(string colors, vector<int> &neededTime)
    {

        int n = colors.size(), res = 0, maxTime = 0;

        for (int i = 0; i < n; i++)
        {
            if (i > 0 && colors[i] != colors[i - 1])
                maxTime = 0;

            res += min(maxTime, neededTime[i]);
            maxTime = max(maxTime, neededTime[i]);
        }

        return res;
    }
};

// Time : O(n)
// Space : O(1)

/*---------------------------------------------------------------------------------------------------------------------*/

/*

Topic Tags : Greedy, String

For a group of continuous same characters,
we need to delete all the group but leave only one character.

For each group of continuous same characters,
we need time = sum_of_neededTime(group) - max_of_neededTime(group)
to make rope colorful

*/