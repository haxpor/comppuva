/**
 * Problem 102 - Binary Tree Level Order Traversal 
 *
 * Format of testcase.txt is as follows
 *
 * Number of testcases
 * TC#1 Array of numbers to form a binary tree with -9999 as null node
 * TC#1 Array of array of numbers for expect level-nodes
 * TC#2 ... and so on
 *
 * Time complexity: O(2^N)
 * Space complexity: O(N)
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
#include <cmath>
#include "ArrayInputParser.h"

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    std::vector<std::vector<int>> levelOrder(TreeNode* root) {
        if (root == nullptr)
            return {};

        std::vector<std::vector<int>> res (getDepth(root));
        dfsPreorder(root, res, 0);

        return res;
    }
private:
    int getDepth(const TreeNode* root) {
        if (root == nullptr)
            return 0;
        return std::max(getDepth(root->left), getDepth(root->right)) + 1;
    }
    void dfsPreorder(const TreeNode* node, std::vector<std::vector<int>>& res, int depth) {
        if (node == nullptr)
            return;
        
        res[depth].push_back(node->val);
        ++depth;

        dfsPreorder(node->left, res, depth);
        dfsPreorder(node->right, res, depth);
    }
};

#define NULL_NODE -9999

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

    void printBFS(const TreeNode* root) const {
        if (root == nullptr)
            return;

        std::queue<const TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            const TreeNode* node = q.front();
            q.pop();

            if (node == nullptr)
                std::cout << "null ";
            else {
                std::cout << node->val << ' ';

                if (node->left)
                    q.push(node->left);
                else if (node->right)
                    q.push(nullptr);

                if (node->right)
                    q.push(node->right);
                else if (node->left)
                    q.push(nullptr);
            }
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
        // read in input array of numbers to form binary tree
        std::getline(infile, line);
        std::vector<int> nums = aparser.parse<int>(line);
        // form binary tree
        TreeNode* inputTree = util.constructTree(nums);

        // read in input array of array of numbers to form expect output
        std::getline(infile, line);
        std::vector<std::vector<int>> expectNums = aparser.parse<std::vector<int>>(line);

        // compute
        std::vector<std::vector<int>> out = sol.levelOrder(inputTree);
        if (out.size() != expectNums.size()) {
            std::printf("[Failed #%d] Size mismatch. Output=%ld, Expect=%ld\n", i, out.size(), expectNums.size());
        }
        else {
            bool isFailed = false;
            for (int j=0; j<out.size(); ++j) {
                if (out[j] != expectNums[j]) {
                    std::printf("[Failed #%d] Element mismatch at index %d\n", i, j);
                    isFailed = true;
                    break;
                }
            }

            if (!isFailed)
                std::printf("[Success #%d]\n", i);
        }
    }

    infile.close();

    return 0;
}
