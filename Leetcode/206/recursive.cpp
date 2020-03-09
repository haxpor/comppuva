/**
 * Problem 206 - Reverse Linked List 
 *
 * Format of testcase.txt is as follows
 *
 * Number of testcases
 * TC#1 Input array of number for linked list
 * TC#1 Input array of number for linked list as expect for output
 * TC#2 ... and so on
 *
 * Time complexity: O(N)
 * Space complexity: O(1) (2 auxiliary variables as dummy starting node, and pointer node)
 */
#include <vector>
#include <cassert>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdio>
#include "ArrayInputParser.h"

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr)
            return nullptr;

        ListNode res (-99);
        ListNode* nodeptr = &res;
        dfs(head, &nodeptr);
        nodeptr->next = nullptr;    // as it's in-place, terminate the list

        return res.next;
    }
private:
    void dfs(const ListNode* node, ListNode** res) {
        if (node == nullptr)
            return;

        dfs(node->next, res);
        (*res)->next = const_cast<ListNode*>(node);
        (*res) = (*res)->next;
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

    for (int i=0; i<N; ++i)
    {
        // read input linked list
        std::getline(infile, line);
        std::vector<int> nums = aparser.parse<int>(line);

        ListNode* nodeptr = nullptr;    // shared temp node

        // form linked list
        ListNode inputLinkedList(-99);  // dummy starting node
        nodeptr = &inputLinkedList;
        for (const auto& n : nums) {
            nodeptr->next = new ListNode(n);
            nodeptr = nodeptr->next;
        }

        // read expect output linked list
        std::getline(infile, line);
        std::vector<int> expectNums = aparser.parse<int>(line);

        // form linked list
        ListNode expectLinkedList (-99);    // dummy starting node
        nodeptr = &expectLinkedList;
        for (const auto& n : expectNums) {
            nodeptr->next = new ListNode(n);
            nodeptr = nodeptr->next;
        }

        // compute
        ListNode* out = sol.reverseList(inputLinkedList.next);

        if (out == nullptr && expectLinkedList.next == nullptr) {
            std::printf("[Success #%d]\n", i);
        }
        else if (out == nullptr && expectLinkedList.next != nullptr) {
            std::printf("[Failed #%d]\n", i);
        }
        else if (out != nullptr && expectLinkedList.next == nullptr) {
            std::printf("[Failed #%d]\n", i);
        }
        else {
            std::vector<int> av;
            ListNode* nodeptr = out;
            while (nodeptr) {
                av.push_back(nodeptr->val);
                nodeptr = nodeptr->next;
            }

            std::vector<int> bv;
            nodeptr = expectLinkedList.next;
            while (nodeptr) {
                bv.push_back(nodeptr->val);
                nodeptr = nodeptr->next;
            }

            if (av == bv) {
                std::printf("[Success #%d]\n", i);
            }
            else {
                std::printf("[Fail #%d]\n", i);
            }
        }
    }

    infile.close();

    return 0;
}
