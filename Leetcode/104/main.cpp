/**
 * Problem 104 - Maximum Depth of Binary Tree 
 *
 * Format of testcase.txt is as follows
 *
 * Number of testcases
 * TC#1 Array of number whose -9999 indicates null; for input of binary tree.
 * TC#1 Expect depth of tree.
 * TC#2 ... and so on
 *
 * Time complexity: O(N) (N is number of nodes)
 * Space complexity: O(1)
 */
#include <vector>
#include <cassert>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include "ArrayInputParser.h"

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == nullptr)
            return 0;

        int leftDepth = maxDepth(root->left);
        int rightDepth = maxDepth(root->right);

        return std::max(leftDepth, rightDepth) + 1;
    }
};

class Util {
public:
    // form a binary tree from input of array of numbers
    // `i` is the indexed-level of node in the binary tree
    // See https://www.geeksforgeeks.org/construct-complete-binary-tree-given-array/
    TreeNode* insertLevelOrder(const std::vector<int>& nums, int i) {
        if (i >= nums.size())
            return nullptr;

        if (nums[i] == -9999)
            return nullptr;

        TreeNode* node = new TreeNode(nums[i]);

        node->left = insertLevelOrder(nums, 2*i + 1);
        node->right = insertLevelOrder(nums, 2*i + 2);

        return node;
    }

    void printInOrder(TreeNode* root) {
        if (root != nullptr) {
            printInOrder(root->left);
            std::cout << root->val << ' ';
            printInOrder(root->right);
        }
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
        // note: fixed -9999 as null node
        std::getline(infile, line);
        std::vector<int> nums = aparser.parse<int>(line);
        // forming a binary tree
        TreeNode* root = util.insertLevelOrder(nums, 0);

        // read depth of binary tree
        int expect;
        infile >> expect;
        infile.ignore();

        // compute
        int out = sol.maxDepth(root);
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
