/*

Problem Link : https://leetcode.com/problems/add-one-row-to-tree/

623. Add One Row to Tree

Given the root of a binary tree and two integers val and depth,
add a row of nodes with value val at the given depth depth.

Note that the root node is at depth 1.

The adding rule is:

Given the integer depth, for each not null tree node cur at the depth depth - 1,
create two tree nodes with value val as cur's left subtree root and right subtree root.

cur's original left subtree should be the left subtree of the new left subtree root.

cur's original right subtree should be the right subtree of the new right subtree root.

If depth == 1 that means there is no depth depth - 1 at all, then create a tree node with value val as the new root of the whole original tree, and the original tree is the new root's left subtree.

Input: root = [4,2,6,3,1,5], val = 1, depth = 2
Output: [4,1,1,2,null,null,6,3,1,5]

Input: root = [4,2,null,3,1], val = 1, depth = 3
Output: [4,2,null,1,1,3,null,null,1]


Constraints:

The number of nodes in the tree is in the range [1, 104].
The depth of the tree is in the range [1, 104].
-100 <= Node.val <= 100
-105 <= val <= 105
1 <= depth <= the depth of tree + 1

*/

/*------------------------------------------------------------------------------------------------------*/

// Using Recursion :

class Solution
{
public:
    TreeNode *addOneRow(TreeNode *root, int val, int depth)
    {

        if (depth == 1)
        {
            TreeNode *newRoot = new TreeNode(val);
            newRoot->left = root;
            return newRoot;
        }

        queue<TreeNode *> q;
        q.push(root);
        int level = 1;
        while (!q.empty())
        {
            int size = q.size();
            for (int i = 0; i < size; i++)
            {
                TreeNode *node = q.front();
                q.pop();

                if (level == depth - 1)
                {
                    TreeNode *newLeft = new TreeNode(val);
                    newLeft->left = node->left;
                    node->left = newLeft;

                    TreeNode *newRight = new TreeNode(val);
                    newRight->right = node->right;
                    node->right = newRight;

                    if (i == size - 1)
                        return root;
                }

                if (node->left)
                    q.push(node->left);

                if (node->right)
                    q.push(node->right);
            }
            level++;
        }

        return root;
    }
};

// Time : O(n)
// Space : O(n)

/*-------------------------------------------------------------------------------------------------------*/

/*
Topic Tags : Breath FIrt Search, Binary Tree

Approach :
Go row by row to the row at depth d - 1, then insert the new nodes there.
*/