// Problem Link : https://leetcode.com/problems/path-sum/
/*
112. Path Sum

Given the root of a binary tree and an integer targetSum, return true if the tree has a root-to-leaf
path such that adding up all the values along the path equals targetSum.
A leaf is a node with no children.

Input: root = [5,4,8,11,null,13,4,7,2,null,null,null,1], targetSum = 22
Output: true
(5 --> 4 --> 11--> 2): The sum is 22
Explanation: The root-to-leaf path with the target sum is shown.

Input: root = [1,2,3], targetSum = 5
Output: false
Explanation: There two root-to-leaf paths in the tree:
(1 --> 2): The sum is 3.
(1 --> 3): The sum is 4.
There is no root-to-leaf path with sum = 5.

Input: root = [], targetSum = 0
Output: false
Explanation: Since the tree is empty, there are no root-to-leaf paths.

The number of nodes in the tree is in the range [0, 5000].
-1000 <= Node.val <= 1000
-1000 <= targetSum <= 1000

*/

/*-------------------------------------------------------------------------------------------------------------*/

// Using Recursion

class Solution
{
public:
    bool isleaf(TreeNode *root)
    {
        if (root->left == nullptr && root->right == nullptr)
            return true;

        return false;
    }

    bool solve(TreeNode *root, int targetSum)
    {
        if (root == nullptr)
            return false;

        if (isleaf(root) && root->val != targetSum)
            return false;

        if (isleaf(root) && root->val == targetSum)
            return true;

        return solve(root->left, targetSum - root->val) ||
               solve(root->right, targetSum - root->val);
    }

    bool hasPathSum(TreeNode *root, int targetSum)
    {

        return solve(root, targetSum);
    }
};

// Time : O(n)
// Space : O(1)
// Auxiliary recursion stack space is there

/*-------------------------------------------------------------------------------------------------------------*/

/*

Topic Tags : Binary Tree, DFS

The basic idea is to subtract the value of current node from sum until it reaches a leaf node and
the subtraction equals 0, then we know that we got a hit.
Otherwise the subtraction at the end could not be 0.

*/