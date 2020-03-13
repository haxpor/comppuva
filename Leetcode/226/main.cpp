/**
 * Problem 226 - Invert Binary Tree https://leetcode.com/problems/invert-binary-tree/ 
 *
 * Format of testcase.txt is as follows
 *
 * Number of testcases
 * TC#1 Array of numbers to form a binary tree
 * TC#1 Array of numbers to form an expect binary tree
 * TC#2 ... and so on
 *
 * Time complexity: O(N)
 * Space complexity: O(h) wheres h is the height of the tree
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
#include "ArrayInputParser.h"

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (!root)
            return nullptr;

        TreeNode* left = invertTree(root->left);
        TreeNode* right = invertTree(root->right);
        root->left = right;
        root->right = left;
        return root;
    }
};

#define NULL_NODE -9999

class Util {
public:
    // form a binary tree from input of array of numbers
    // `i` is the indexed-level of node in the binary tree
    // See https://www.geeksforgeeks.org/construct-complete-binary-tree-given-array/
    TreeNode* insertLevelOrder(const std::vector<int>& nums, int i) const {
        if (i >= nums.size())
            return nullptr;

        if (nums[i] == NULL_NODE)
            return nullptr;

        TreeNode* node = new TreeNode(nums[i]);

        node->left = insertLevelOrder(nums, 2*i + 1);
        node->right = insertLevelOrder(nums, 2*i + 2);

        return node;
    }

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
        // read in array of numbers to form input binary tree
        std::getline(infile, line);
        std::vector<int> nums = aparser.parse<int>(line);
        // form a binary tree
        TreeNode* tree = util.constructTree(nums);

        // read in array of numbers to form an exepct binary tree
        std::getline(infile, line);
        std::vector<int> expectNums = aparser.parse<int>(line);
        // form a binary tree
        TreeNode* expectTree = util.constructTree(expectNums);

        // compute
        TreeNode* outTree = sol.invertTree(tree);

        if (util.isSameTree(outTree, expectTree))
            std::printf("[Success #%d]\n", i);
        else
            std::printf("[Failed #%d] Tree mismatch\n", i);

        util.deleteTree(tree);
        util.deleteTree(expectTree);
    }

    infile.close();

    return 0;
}
