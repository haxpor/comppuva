/**
 * Problem 100 - Same Tree - https://leetcode.com/problems/same-tree/ 
 *
 * Format of testcase.txt is as follows
 *
 * Number of testcases
 * TC#1 Input array of numbers for binary tree 1
 * TC#1 Input array of numbers for binary tree 2
 * TC#1 Expect boolean output whether both trees are the same or not; either "true" or "false"
 * TC#2 ... and so on
 *
 * Time complexity: O(N) where N is |p|+|q|
 * Space complexity: O(N) where N is |p|+|q|
 */
#include <vector>
#include <cassert>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdio>
#include "ArrayInputParser.h"

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
};

#define NULL_NODE -9999

class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (p == nullptr && q == nullptr)
            return true;          
        if (p == nullptr && q != nullptr)
            return false;
        if (p != nullptr && q == nullptr)
            return false;

        std::vector<int> plist;
        std::vector<int> qlist;

        preOrderTraversal(p, plist);
        preOrderTraversal(q, qlist);

        return plist == qlist;
    }
private:
    void preOrderTraversal(const TreeNode* node, std::vector<int>& list) {
        if (node == nullptr) {
            list.push_back(NULL_NODE);
            return;
        }
        
        list.push_back(node->val);
        preOrderTraversal(node->left, list);
        preOrderTraversal(node->right, list);
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

        if (nums[i] == NULL_NODE)
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
        // read array of numbers for input binary tree 1
        std::getline(infile, line);
        std::vector<int> nums = aparser.parse<int>(line);
        // form binary tree 1
        TreeNode* tree1 = util.insertLevelOrder(nums, 0);

        // read array of numbers for input binary tree 2
        std::getline(infile, line);
        nums = aparser.parse<int>(line);
        // form binary tree 2
        TreeNode* tree2 = util.insertLevelOrder(nums, 0);

        // read expect result
        bool expect;
        infile >> std::boolalpha >> expect;
        infile.ignore();

        // compute
        bool out = sol.isSameTree(tree1, tree2);
        if (out == expect)
        {
            std::printf("[Success #%d] Output = %s, Expect = %s\n", i, out?"true":"false", expect?"true":"false");
        }
        else
        {
            std::printf("[Failed #%d] Output = %s, Expect = %s\n", i, out?"true":"false", expect?"true":"false");
        }
    }

    infile.close();

    return 0;
}
