/**
 * Problem 124 - Binary Tree Maximum Path Sum 
 *
 * Format of testcase.txt is as follows
 *
 * Number of testcases
 * TC#1 Array of numbers with -9999 as null for binary tree
 * TC#1 Expect output
 * TC#2 ... and so on
 *
 * Time complexity: O(N)
 * Space complexity: O(h) where h is the height of the binary tree
 */
#include <vector>
#include <cassert>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <climits>
#include "ArrayInputParser.h"

#define NULL_NODE -9999

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    int maxPathSum(TreeNode* root) {
        if (root == nullptr)
            return 0;

        int sum = INT_MIN;
        dfs(root, sum);
        return sum;
    }

private:
    int dfs(const TreeNode* root, int& sum) {
        if (root == nullptr)
            return 0;

        int left = dfs(root->left, sum);
        int right = dfs(root->right, sum);

        int onePathSum = root->val + std::max(0, std::max(left, right));
        sum = std::max(sum, std::max(onePathSum, root->val + left + right));

        // as this dfs() function only computes sum of one-path value
        return onePathSum;
    }
};

class Util {
public:
    TreeNode* constructTree(const std::vector<int>& nums) {
        std::unordered_map<int, TreeNode*> lookup;
        for (const auto& n : nums) {
            if (n != NULL_NODE)
                lookup[n] = new TreeNode(n);
        }

        return constructTree_(nums, lookup);
    }

    void printInOrder(TreeNode* root) const {
        if (root != nullptr) {
            printInOrder(root->left);
            std::cout << root->val << ' ';
            printInOrder(root->right);
        }
    }

    void printPreOrder(TreeNode* root) const {
        if (root) {
            std::cout << root->val << ' ';
            printPreOrder(root->left);
            printPreOrder(root->right);
        }
        else {
            std::cout << "null ";
        }
    }

    // after this pointer will become invalid
    void deleteTree(TreeNode* root) const {
        if (!root)
            return;

        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }

    bool isSameTree(TreeNode* p, TreeNode* q) const {
        if (p == nullptr && q == nullptr)
            return true;
        if (p == nullptr || q == nullptr)
            return false;
        if (p->val != q->val)
            return false;

        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
private:
    TreeNode* constructTree_(const std::vector<int>& nums, std::unordered_map<int, TreeNode*>& lookup) {
        if (nums.size() == 0)
            return nullptr;

        TreeNode* res = lookup[nums[0]];
        std::queue<TreeNode*> queue;
        queue.push(res);
        int elemi = 1;
        while (!queue.empty() && elemi < nums.size()) {
            TreeNode* nodeptr = queue.front();
            queue.pop();

            if (nums[elemi] != NULL_NODE) {
                nodeptr->left = lookup[nums[elemi++]];
                queue.push(nodeptr->left);
            }
            else {
                nodeptr->left = nullptr;
                ++elemi;
            }

            if (elemi >= nums.size())
                break;

            if (nums[elemi] != NULL_NODE) {
                nodeptr->right = lookup[nums[elemi++]];
                queue.push(nodeptr->right);
            }
            else {
                nodeptr->right = nullptr;
                ++elemi;
            }
        }

        return res;
    }
};

int main()
{
    std::ifstream infile("testcases.txt");
    std::string line;

    int N;
    infile >> N;    // read number of testcases
    infile.ignore();

    Solution sol;
    ArrayInputParser aparser;
    Util util;

    for (int i=0; i<N; ++i)
    {
        // read in array of numbers to form binary tree
        std::getline(infile, line);
        std::vector<int> nums = aparser.parse<int>(line);
        TreeNode* inputTree = util.constructTree(nums);

        // read in expect maximum path sum
        int expect;
        infile >> expect;
        infile.ignore();

        // compute
        int out = sol.maxPathSum(inputTree);
        if (out == expect)
        {
            std::printf("[Success #%d] Output = %d, Expect = %d\n", i, out, expect);
        }
        else
        {
            std::printf("[Failed #%d] Output = %d, Expect = %d\n", i, out, expect);
        }
    }

    infile.close();

    return 0;
}
